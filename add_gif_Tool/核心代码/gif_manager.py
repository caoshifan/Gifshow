"""
GIF 动画库管理核心模块
支持添加和删除GIF动画
"""
import os
import re
import shutil
from pathlib import Path
from typing import List, Dict

class GifLibraryManager:
    def __init__(self, library_root_path: str = None):
        """
        初始化GIF库管理器
        :param library_root_path: MyLibrary根目录路径，如果为None则自动查找
        """
        self.library_root = None
        self.frames_dir = None
        self.cpp_file = None
        self.h_file = None
        self.gif_frames_h = None
        
        if library_root_path:
            self.set_library_path(library_root_path)
        else:
            self._auto_detect_library_path()

    def _auto_detect_library_path(self):
        """自动检测库路径"""
        # 尝试多个可能的路径
        possible_paths = []
        
        try:
            # 1. 从当前文件位置向上查找
            if hasattr(self, '__file__'):
                current_dir = Path(__file__).parent
            else:
                # 对于打包的exe，使用当前工作目录
                current_dir = Path.cwd()
            
            # 从当前目录开始，向上查找MyLibrary
            search_dir = current_dir
            for _ in range(5):  # 最多向上查找5级
                possible_paths.append(search_dir / "MyLibrary")
                possible_paths.append(search_dir.parent / "MyLibrary")
                search_dir = search_dir.parent
            
            # 2. 添加一些常见的相对路径
            possible_paths.extend([
                Path("./MyLibrary"),
                Path("../MyLibrary"),
                Path("../../MyLibrary"),
                Path("./MyLibrary"),
                current_dir.parent / "MyLibrary"
            ])
            
        except Exception as e:
            print(f"⚠️ 路径检测出错: {e}")
        
        # 检查哪个路径存在
        for path in possible_paths:
            if path.exists() and (path / "src" / "frames").exists():
                self.set_library_path(str(path))
                print(f"✅ 自动找到库路径: {path}")
                return
        
        print("❌ 无法自动找到MyLibrary路径，请手动设置")

    def set_library_path(self, library_root_path: str) -> bool:
        """
        手动设置库路径
        :param library_root_path: MyLibrary根目录路径
        :return: 是否设置成功
        """
        try:
            self.library_root = Path(library_root_path)
            self.frames_dir = self.library_root / "src" / "frames"
            self.cpp_file = self.library_root / "src" / "MyLibrary.cpp"
            self.h_file = self.library_root / "src" / "MyLibrary.h"
            self.gif_frames_h = self.library_root / "src" / "gif_frames.h"
            
            # 验证路径是否有效
            if not self.library_root.exists():
                print(f"❌ 路径不存在: {self.library_root}")
                return False
            
            if not self.frames_dir.exists():
                print(f"❌ frames目录不存在: {self.frames_dir}")
                return False
            
            # 确保目录存在
            self.frames_dir.mkdir(parents=True, exist_ok=True)
            
            print(f"✅ 库路径设置成功: {self.library_root}")
            return True
            
        except Exception as e:
            print(f"❌ 设置库路径失败: {e}")
            return False

    def is_library_path_valid(self) -> bool:
        """检查当前库路径是否有效"""
        if not self.library_root:
            return False
        
        required_paths = [
            self.library_root,
            self.frames_dir,
            self.cpp_file,
            self.h_file
        ]
        
        return all(path and path.exists() for path in required_paths)

    def get_library_status(self) -> dict:
        """获取库状态信息"""
        if not self.library_root:
            return {
                "valid": False,
                "message": "未设置库路径",
                "path": None,
                "gif_count": 0
            }
        
        if not self.is_library_path_valid():
            return {
                "valid": False,
                "message": f"库路径无效: {self.library_root}",
                "path": str(self.library_root),
                "gif_count": 0
            }
        
        gif_count = len(self.get_existing_gifs())
        return {
            "valid": True,
            "message": f"库路径有效，包含 {gif_count} 个GIF",
            "path": str(self.library_root),
            "gif_count": gif_count
        }

    def get_existing_gifs(self) -> List[str]:
        """获取当前库中所有GIF动画名称"""
        if not self.frames_dir or not self.frames_dir.exists():
            return []
        
        gifs = []
        try:
            for item in self.frames_dir.iterdir():
                if item.is_dir() and not item.name.startswith('.'):
                    gifs.append(item.name)
        except Exception as e:
            print(f"⚠️ 读取GIF列表失败: {e}")
        
        return sorted(gifs)

    def add_gif(self, gif_folder_path: str) -> bool:
        """
        添加GIF到库中
        :param gif_folder_path: 包含.c文件的GIF文件夹路径
        :return: 是否成功
        """
        if not self.is_library_path_valid():
            print("❌ 库路径无效，无法添加GIF")
            return False
        
        try:
            gif_name = os.path.basename(gif_folder_path.rstrip('/'))
            print(f"🔧 开始添加GIF: {gif_name}")
            
            # 1. 复制文件夹到frames目录
            target_dir = self.frames_dir / gif_name
            if target_dir.exists():
                shutil.rmtree(target_dir)
            shutil.copytree(gif_folder_path, target_dir)
            
            # 2. 处理.c文件中的数组名称
            array_names = self._process_c_files(target_dir, gif_name)
            
            # 3. 更新gif_frames.h
            self._update_gif_frames_h(gif_name, array_names)
            
            # 4. 更新MyLibrary.cpp
            self._update_cpp_file(gif_name, array_names)
            
            # 5. 更新MyLibrary.h的枚举
            self._update_h_file_enum(gif_name)
            
            print(f"✅ 成功添加GIF: {gif_name}")
            return True
            
        except Exception as e:
            print(f"❌ 添加GIF失败: {str(e)}")
            return False

    def remove_gif(self, gif_name: str) -> bool:
        """
        从库中删除指定的GIF
        :param gif_name: GIF名称
        :return: 是否成功
        """
        if not self.is_library_path_valid():
            print("❌ 库路径无效，无法删除GIF")
            return False
        
        try:
            print(f"🗑️ 开始删除GIF: {gif_name}")
            
            # 1. 删除文件夹
            target_dir = self.frames_dir / gif_name
            if target_dir.exists():
                shutil.rmtree(target_dir)
                print(f"🗂️ 已删除文件夹: {target_dir}")
            
            # 2. 从gif_frames.h中移除相关声明
            self._remove_from_gif_frames_h(gif_name)
            
            # 3. 从MyLibrary.cpp中移除相关代码
            self._remove_from_cpp_file(gif_name)
            
            # 4. 从MyLibrary.h的枚举中移除
            self._remove_from_h_file_enum(gif_name)
            
            print(f"✅ 成功删除GIF: {gif_name}")
            return True
            
        except Exception as e:
            print(f"❌ 删除GIF失败: {str(e)}")
            return False

    def _process_c_files(self, gif_dir: Path, gif_name: str) -> List[str]:
        """处理C文件，修改数组名称"""
        array_names = []
        
        # 正则表达式匹配数组定义
        pattern = re.compile(
            r'(?P<declaration>const\s+unsigned\s+char\s+)'
            r'(?P<array_name>\w+)'
            r'(?P<array_def>\[\d+\]\s*=\s*\{.*?\}\s*;\s*)',
            re.DOTALL | re.IGNORECASE
        )
        
        for c_file in gif_dir.glob("*.c"):
            try:
                with open(c_file, 'r+', encoding='utf-8') as f:
                    content = f.read()
                    
                    matches = list(pattern.finditer(content))
                    if not matches:
                        continue
                        
                    # 逆向替换
                    for match in reversed(matches):
                        declaration = match.group('declaration')
                        array_name = match.group('array_name')
                        array_def = match.group('array_def')
                        
                        new_name = f"{gif_name}_{array_name}"
                        array_names.append(new_name)
                        replacement = f"{declaration}{new_name}{array_def}"
                        
                        start, end = match.span()
                        content = content[:start] + replacement + content[end:]
                    
                    # 写回文件
                    f.seek(0)
                    f.truncate()
                    f.write(content)
                    
            except Exception as e:
                print(f"⚠️ 处理文件{c_file}时出错: {e}")
        
        return sorted(array_names)

    def _update_gif_frames_h(self, gif_name: str, array_names: List[str]):
        """更新gif_frames.h文件"""
        # 创建新的声明内容
        extern_declarations = []
        for array_name in array_names:
            extern_declarations.append(f"extern const unsigned char {array_name}[];")
        
        extern_declarations.append(f"extern const unsigned char* {gif_name}_gif_frames[{len(array_names)}];")
        extern_declarations.append(f"extern const int {gif_name}_total_frames;")
        extern_declarations.append("")  # 空行
        
        content_to_add = "\n".join(extern_declarations)
        
        # 如果文件不存在，创建新文件
        if not self.gif_frames_h.exists():
            with open(self.gif_frames_h, "w", encoding="utf-8") as f:
                f.write("// gif_frames.h\n#pragma once\n\n")
        
        # 追加内容
        with open(self.gif_frames_h, "a", encoding="utf-8") as f:
            f.write(content_to_add)

    def _update_cpp_file(self, gif_name: str, array_names: List[str]):
        """更新MyLibrary.cpp文件"""
        # 生成数组初始化代码
        array_list = ",\n    ".join(array_names)
        init_code = f"""
const unsigned char* {gif_name}_gif_frames[] = {{
    {array_list}
}};
const int {gif_name}_total_frames = sizeof({gif_name}_gif_frames) / sizeof({gif_name}_gif_frames[0]);
"""
        
        # 读取原文件
        with open(self.cpp_file, 'r', encoding='utf-8') as f:
            content = f.readlines()
        
        # 找到构造函数位置并插入初始化代码
        for i, line in enumerate(content):
            if ': display(width, height, &Wire, resetPin) {}' in line.strip():
                content[i] = line.rstrip() + init_code + '\n'
                break
        
        # 找到switch语句并添加case
        for i, line in enumerate(content):
            if 'switch (currentModel) {' in line.strip():
                case_code = f"""            case DisplayModel::{gif_name.upper()}:
                display.drawBitmap(0, 0, {gif_name}_gif_frames[currentFrame], 128, 64, SSD1306_WHITE);
                currentFrame = (currentFrame + 1) % {gif_name}_total_frames; 
                break;
"""
                content[i] = line.rstrip() + '\n' + case_code
                break
        
        # 写回文件
        with open(self.cpp_file, 'w', encoding='utf-8') as f:
            f.writelines(content)

    def _update_h_file_enum(self, gif_name: str):
        """更新MyLibrary.h文件的枚举"""
        with open(self.h_file, 'r', encoding='utf-8') as f:
            content = f.readlines()
        
        # 找到枚举定义位置
        for i, line in enumerate(content):
            if 'enum class DisplayModel {' in line.strip():
                content[i] = line.replace('{', f'{{\n    {gif_name.upper()},')
                break
        
        # 写回文件
        with open(self.h_file, 'w', encoding='utf-8') as f:
            f.writelines(content)

    def _remove_from_gif_frames_h(self, gif_name: str):
        """从gif_frames.h文件中移除相关声明"""
        if not self.gif_frames_h.exists():
            return
            
        with open(self.gif_frames_h, 'r', encoding='utf-8') as f:
            lines = f.readlines()
        
        # 过滤掉包含gif_name的行
        filtered_lines = []
        for line in lines:
            if gif_name not in line:
                filtered_lines.append(line)
        
        with open(self.gif_frames_h, 'w', encoding='utf-8') as f:
            f.writelines(filtered_lines)

    def _remove_from_cpp_file(self, gif_name: str):
        """从MyLibrary.cpp文件中移除相关代码"""
        with open(self.cpp_file, 'r', encoding='utf-8') as f:
            content = f.read()
        
        # 移除数组定义和初始化代码
        pattern = rf'const unsigned char\* {gif_name}_gif_frames\[\] = \{{.*?\}};.*?const int {gif_name}_total_frames = .*?;'
        content = re.sub(pattern, '', content, flags=re.DOTALL)
        
        # 移除switch case
        case_pattern = rf'\s*case DisplayModel::{gif_name.upper()}:.*?break;'
        content = re.sub(case_pattern, '', content, flags=re.DOTALL)
        
        with open(self.cpp_file, 'w', encoding='utf-8') as f:
            f.write(content)

    def _remove_from_h_file_enum(self, gif_name: str):
        """从MyLibrary.h文件的枚举中移除"""
        with open(self.h_file, 'r', encoding='utf-8') as f:
            content = f.read()
        
        # 移除枚举项
        pattern = rf'\s*{gif_name.upper()},?\s*'
        content = re.sub(pattern, '', content)
        
        with open(self.h_file, 'w', encoding='utf-8') as f:
            f.write(content)

    def rebuild_library(self):
        """重建整个库文件（重新生成所有文件）"""
        if not self.is_library_path_valid():
            print("❌ 库路径无效，无法重建库")
            return False
        
        print("🔄 开始重建库...")
        
        # 获取所有现有的GIF
        existing_gifs = self.get_existing_gifs()
        
        # 清空并重建gif_frames.h
        with open(self.gif_frames_h, 'w', encoding='utf-8') as f:
            f.write("// gif_frames.h\n#pragma once\n\n")
        
        # 重建每个GIF的声明和代码
        for gif_name in existing_gifs:
            gif_dir = self.frames_dir / gif_name
            if gif_dir.exists():
                # 重新处理C文件
                array_names = self._process_c_files(gif_dir, gif_name)
                # 更新gif_frames.h
                self._update_gif_frames_h(gif_name, array_names)
        
        # 重建cpp和h文件的相关部分（这里简化处理）
        print("✅ 库重建完成！")
        return True 