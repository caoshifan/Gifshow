"""
简单脚本：列出当前库中的所有GIF动画
"""
from gif_manager import GifLibraryManager

def list_all_gifs():
    """列出并显示所有GIF的详细信息"""
    print("📋 GIF动画库内容列表")
    print("=" * 40)
    
    # 初始化管理器
    manager = GifLibraryManager()
    
    # 获取所有GIF
    gifs = manager.get_existing_gifs()
    
    if not gifs:
        print("❌ 库中没有找到任何GIF动画")
        return
    
    print(f"📊 总计: {len(gifs)} 个GIF动画\n")
    
    # 显示每个GIF的详细信息
    for i, gif_name in enumerate(gifs, 1):
        print(f"{i}. 📁 {gif_name}")
        
        # 获取详细信息
        gif_dir = manager.frames_dir / gif_name
        if gif_dir.exists():
            c_files = list(gif_dir.glob("*.c"))
            file_size = sum(f.stat().st_size for f in c_files) / 1024
            print(f"   📊 帧数: {len(c_files)}")
            print(f"   💾 大小: {file_size:.2f} KB")
            print(f"   📂 路径: {gif_dir}")
        else:
            print("   ❌ 文件夹不存在")
        print()
    
    print("=" * 40)
    print("✅ 列表显示完成")

if __name__ == "__main__":
    list_all_gifs() 