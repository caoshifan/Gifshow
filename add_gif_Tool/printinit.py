import os
import re
array_names = []
def rename_array_in_file(file_path,array_names):
    """
    改进版数组重命名函数，支持：
    - 跨行数组定义
    - 带前置注释/空格的声明
    - Windows换行符
    """
    # 增强型正则表达式（移除行首锚定，支持多行）

    pattern = re.compile(
        r'(?P<declaration>const\s+unsigned\s+char\s+)'
        r'(?P<array_name>\w+)'  # 匹配数组名称，不限定具体格式
        r'(?P<array_def>\[\d+\]\s*=\s*\{.*?\}\s*;\s*)',
        re.DOTALL | re.IGNORECASE
    )
    try:
        with open(file_path, 'r+', encoding='utf-8', newline='') as f:
            content = f.read()

            # 查找所有匹配项
            matches = list(pattern.finditer(content))
            if not matches:
                print(f"⚠️ 未找到标准数组定义: {os.path.basename(file_path)}")
                return False

            # 逆向替换
            modified = False
            for match in reversed(matches):
                array_name = match.group('array_name')
                array_names.append(array_name)
                modified = True

            if modified:
                # 保留原始换行符风格
                f.seek(0)
                f.truncate()
                f.write(content)
                return True
            return False

    except UnicodeDecodeError:
        print(f"⛔ 编码错误: {file_path} 可能不是UTF-8文本文件")
        return False


def process_folder(folder_path):
    """
    处理整个文件夹的主函数
    """
    # 获取文件夹名称作为前缀
    folder_name = os.path.basename(folder_path.rstrip('/'))
    print(f"🔧 开始处理文件夹: {folder_name}")
    # 遍历所有.c文件
    modified_count = 0
    for filename in os.listdir(folder_path):
        if filename.endswith('.c'):
            file_path = os.path.join(folder_path, filename)
            # print(f"🔄 正在处理: {filename}")

            if rename_array_in_file(file_path,array_names):
                modified_count += 1
            else:
                print(f"⚠️ 未找到数组定义: {filename}")
    init_code = ",\n    ".join(array_names)
    init_code = f"const unsigned char* {folder_name}_gif_frames[] = {{\n    {init_code}\n}};\nconst int {folder_name}_total_frames = sizeof({folder_name}_gif_frames) / sizeof({folder_name}_gif_frames[0]);"
    return init_code

def update_file(path):
    style_name = os.path.basename(path.rstrip('/'))
    parent_folder = os.path.dirname(os.path.dirname(path))
    print(f"上一层文件夹路径: {parent_folder}")

    # 检测上一层文件夹下是否有 MyLibrary.cpp 文件
    target_file = os.path.join(parent_folder, "MyLibrary.cpp")

    if os.path.exists(target_file) and os.path.isfile(target_file):
        print(f"文件存在: {target_file}")
    else:
        print(f"文件不存在: {target_file}")

    # 需修改的文件名称
    filename = os.path.join(parent_folder,"MyLibrary.cpp")
    # 要添加的代码（请根据需要修改）
    new_code = process_folder(path)

    try:
        # 读取原始文件内容
        with open(filename, 'r', encoding='utf-8') as file:
            content = file.readlines()
        # 找到插入点
        insert_init_line = -1
        insert_case_line = -1
        insert_mylib_line = -1
        for i, line in enumerate(content):
            if ': display(width, height, &Wire, resetPin) {}' in line.strip():
                insert_init_line = i
                break
        for j, line in enumerate(content):
            if 'switch (currentModel) {' in line.strip():
                insert_case_line = j
                break
        if insert_init_line == -1:
            print("未找到目标构造函数,请检查源文件是否被异常修改")
        else:
            # 修改case代码
            original_case_line = content[insert_case_line].strip()
            modified_case_line = original_case_line.replace('{', '{\n            ' + f"case DisplayModel::{style_name.upper()}:\n                display.drawBitmap(0, 0, {style_name}_gif_frames[currentFrame], 128, 64, SSD1306_WHITE);\n                currentFrame = (currentFrame + 1) % {style_name}_total_frames; \n                break;")
            content[insert_case_line] = '        ' + modified_case_line + '\n'

            # 修改内容初始化代码
            original_line = content[insert_init_line].strip()
            modified_line = original_line.replace('{}', '{}\n\n' + new_code)
            content[insert_init_line] = modified_line + '\n'


            # 写回文件 .cpp文件修改完成
            with open(filename, 'w', encoding='utf-8') as file:
                file.writelines(content)
            print("Mylibrary.cpp文件修改完成")

            # 最后修改MyLibrary.h文件添加case类
            mylibrary_h_path = os.path.join(parent_folder, "MyLibrary.h")
            with open(mylibrary_h_path, 'r', encoding='utf-8') as file:
                mylib_content = file.readlines()
            for i, line in enumerate(mylib_content):
                if 'enum class DisplayModel {' in line.strip():
                    insert_mylib_line = i
                    break
            if insert_mylib_line == -1:
                print("未找到mylib.h目标构造函数，请检查源文件是否被异常修改")
            else:
                original_mylib_line = mylib_content[insert_mylib_line].strip()
                modified_mylib_line = original_mylib_line.replace('{', '{\n    ' + f'{style_name.upper()},')
                mylib_content[insert_mylib_line] = modified_mylib_line + '\n'
                with open(mylibrary_h_path, 'w', encoding='utf-8') as file:
                    file.writelines(mylib_content)
                print('Mylibrary.h文件修改完成')

    except FileNotFoundError:
        print(f"找不到文件 {filename}")
    except Exception as e:
        print(f"发生错误: {str(e)}")



if __name__ == "__main__":
    update_file(r"C:\Users\mooncell1997\Desktop\GifPlayer\MyLibrary\src\frames\bath")
