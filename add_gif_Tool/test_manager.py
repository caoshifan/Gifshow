"""
GIF管理器功能测试脚本
"""
from gif_manager import GifLibraryManager
import os

def test_gif_manager():
    print("🧪 开始测试GIF管理器...")
    
    # 初始化管理器
    manager = GifLibraryManager()
    print(f"📁 库目录: {manager.library_root}")
    print(f"📁 帧目录: {manager.frames_dir}")
    
    # 测试获取现有GIF
    print("\n📋 当前库中的GIF:")
    existing_gifs = manager.get_existing_gifs()
    if existing_gifs:
        for i, gif in enumerate(existing_gifs, 1):
            print(f"  {i}. {gif}")
    else:
        print("  (无)")
    
    # 检查关键文件是否存在
    print("\n📂 检查关键文件:")
    files_to_check = [
        manager.cpp_file,
        manager.h_file,
        manager.gif_frames_h,
        manager.frames_dir
    ]
    
    for file_path in files_to_check:
        if file_path.exists():
            print(f"  ✅ {file_path.name}")
        else:
            print(f"  ❌ {file_path.name} (不存在)")
    
    print("\n✅ 测试完成!")

if __name__ == "__main__":
    test_gif_manager() 