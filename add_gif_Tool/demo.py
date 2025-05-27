"""
GIF管理器功能演示脚本
展示如何使用新的管理工具
"""
from gif_manager import GifLibraryManager

def demo_gif_manager():
    print("🎯 GIF动画库管理器 v2.0 功能演示")
    print("="*50)
    
    # 初始化管理器
    manager = GifLibraryManager()
    
    # 显示当前状态
    print("\n📊 当前库状态:")
    existing_gifs = manager.get_existing_gifs()
    print(f"  总GIF数量: {len(existing_gifs)}")
    print(f"  库路径: {manager.library_root}")
    
    # 列出所有GIF
    print("\n📋 当前库中的GIF动画:")
    if existing_gifs:
        for i, gif in enumerate(existing_gifs, 1):
            print(f"  {i}. {gif}")
    else:
        print("  (库中暂无GIF动画)")
    
    # 显示每个GIF的详细信息
    print("\n📝 GIF详细信息:")
    for gif_name in existing_gifs:
        gif_dir = manager.frames_dir / gif_name
        if gif_dir.exists():
            c_files = list(gif_dir.glob("*.c"))
            file_size = sum(f.stat().st_size for f in c_files) / 1024
            print(f"  📁 {gif_name}:")
            print(f"     帧数: {len(c_files)}")
            print(f"     大小: {file_size:.2f} KB")
    
    print("\n" + "="*50)
    print("✨ 新功能展示:")
    print("  ✅ 可视化GIF列表管理")
    print("  ✅ 一键删除不需要的GIF")
    print("  ✅ 图形界面和命令行双支持")
    print("  ✅ 库文件打包导出")
    print("  ✅ 智能库文件重建")
    
    print("\n🚀 使用建议:")
    print("  🎨 图形界面: 运行 python gif_manager_ui.py")
    print("  💻 命令行: 使用 python gif_manager_cli.py --help")
    print("  📦 打包: 使用界面中的打包功能")

if __name__ == "__main__":
    demo_gif_manager() 