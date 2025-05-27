"""
GIF库管理器命令行工具
"""
import argparse
import sys
from gif_manager import GifLibraryManager

def main():
    parser = argparse.ArgumentParser(
        description='GIF动画库管理工具',
        formatter_class=argparse.RawTextHelpFormatter
    )
    
    subparsers = parser.add_subparsers(dest='command', help='可用命令')
    
    # 列出命令
    list_parser = subparsers.add_parser('list', help='列出库中所有GIF')
    
    # 添加命令
    add_parser = subparsers.add_parser('add', help='添加GIF到库')
    add_parser.add_argument('path', type=str, help='GIF文件夹路径')
    
    # 删除命令
    remove_parser = subparsers.add_parser('remove', help='从库中删除GIF')
    remove_parser.add_argument('name', type=str, help='要删除的GIF名称')
    
    # 重建命令
    rebuild_parser = subparsers.add_parser('rebuild', help='重建库文件')
    
    # 信息命令
    info_parser = subparsers.add_parser('info', help='显示GIF信息')
    info_parser.add_argument('name', type=str, help='GIF名称')
    
    args = parser.parse_args()
    
    if not args.command:
        parser.print_help()
        return
    
    # 初始化管理器
    manager = GifLibraryManager()
    
    if args.command == 'list':
        gifs = manager.get_existing_gifs()
        if gifs:
            print(f"库中共有 {len(gifs)} 个GIF动画:")
            for i, gif in enumerate(gifs, 1):
                print(f"  {i}. {gif}")
        else:
            print("库中没有GIF动画")
    
    elif args.command == 'add':
        print(f"正在添加GIF: {args.path}")
        success = manager.add_gif(args.path)
        if success:
            print("✅ 添加成功!")
        else:
            print("❌ 添加失败!")
            sys.exit(1)
    
    elif args.command == 'remove':
        print(f"正在删除GIF: {args.name}")
        success = manager.remove_gif(args.name)
        if success:
            print("✅ 删除成功!")
        else:
            print("❌ 删除失败!")
            sys.exit(1)
    
    elif args.command == 'rebuild':
        print("正在重建库文件...")
        manager.rebuild_library()
        print("✅ 重建完成!")
    
    elif args.command == 'info':
        gif_dir = manager.frames_dir / args.name
        if gif_dir.exists():
            c_files = list(gif_dir.glob("*.c"))
            print(f"GIF名称: {args.name}")
            print(f"帧数: {len(c_files)}")
            print(f"路径: {gif_dir}")
            print(f"文件大小: {sum(f.stat().st_size for f in c_files) / 1024:.2f} KB")
        else:
            print(f"❌ 找不到GIF: {args.name}")
            sys.exit(1)

if __name__ == "__main__":
    main() 