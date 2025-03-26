import re
import os
from pathlib import Path

array_names = []

# 将文件复制到包目录下
# def copy_folder(source_folder, destination_folder):
#     # 如果目标文件夹不存在，则创建它
#     try:
#         if not os.path.exists(destination_folder):
#             os.makedirs(destination_folder)
#
#         # 遍历源文件夹中的所有文件
#         for filename in os.listdir(source_folder):
#             # 检查是否是以 .c 结尾的文件
#             if filename.lower().endswith('.c'):
#                 source_file = os.path.join(source_folder, filename)
#                 # 确保是文件而不是文件夹
#                 if os.path.isfile(source_file):
#                     shutil.copy2(source_file, destination_folder)
#                     return True
#     except FileNotFoundError:
#         return False

def rename_array_in_file(file_path, prefix,array_names):
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
                declaration = match.group('declaration')
                array_name = match.group('array_name')
                array_def = match.group('array_def')

                new_name = f"{prefix}_{array_name}"
                extend_content = f"extern const unsigned char {new_name}[];\n"
                array_names = array_names.append(extend_content)
                replacement = f"{declaration}{new_name}{array_def}"

                start, end = match.span()
                content = content[:start] + replacement + content[end:]
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
            print(f"🔄 正在处理: {filename}")

            if rename_array_in_file(file_path, folder_name,array_names):
                modified_count += 1
            else:
                print(f"⚠️ 未找到数组定义: {filename}")

    print(f"✅ 完成！共修改 {modified_count} 个文件")
    try:
        content_to_add = ''.join(array_names)
        path = Path(folder_path)
        gif_frames_path = path.parents[1] / 'gif_frames.h'
        if os.path.exists(gif_frames_path):
            print('.h文件以存在,默认在后缀添加')
        else:
            print(".h文件不存在，创建新文件")
            file = open(gif_frames_path,"w")
            file.write("// gif_frames.h\n#pragma once\n")
        content_to_add = f"{content_to_add}\nextern const unsigned char* {folder_name}_gif_frames[{modified_count}];\nextern const int {folder_name}_total_frames;\n\n"
        with open(gif_frames_path, "a", encoding="utf-8") as file:
            file.write(content_to_add)
        print(f"成功向文件 {file_path} 添加内容！")
    except Exception as e:
        print(f"发生错误：{e}")


if __name__ == '__main__':
    # 设置命令行参数
    # parser = argparse.ArgumentParser(
    #     description='GIF数组重命名工具 v1.0',
    #     formatter_class=argparse.RawTextHelpFormatter
    # )
    # parser.add_argument(
    #     'path',
    #     type=str,
    #     help='需要处理的文件夹路径（例如：./frames/snow）'
    # )
    #
    # args = parser.parse_args()
    #
    # # 验证路径有效性
    # if not os.path.isdir(args.path):
    #     print(f"❌ 错误：路径 {args.path} 不存在或不是文件夹")
    #     exit(1)
    #
    # # 开始处理
    # process_folder(args.path)
    process_folder(r"C:\Users\mooncell1997\Desktop\GifPlayer\MyLibrary\src\frames\dance")