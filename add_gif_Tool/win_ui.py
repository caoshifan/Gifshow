import tkinter as tk
from tkinter import filedialog, messagebox
from change_arrayname import process_folder
from printinit import update_file
import os

class GIFManagerUI:
    def __init__(self, master):
        self.master = master
        master.title("GIF库管理器")
        master.geometry("400x200")

        # 存储路径的变量
        self.gif_folder_path = None
        self.library_folder_path = None

        # GIF文件夹路径
        self.gif_path_label = tk.Label(master, text="当前GIF路径：未选择", wraplength=350)
        self.gif_path_label.pack(pady=10)

        self.select_gif_btn = tk.Button(
            master,
            text="选择GIF文件夹",
            command=self.select_gif_folder,
            width=20
        )
        self.select_gif_btn.pack(pady=5)

        # # 库文件夹路径
        # self.lib_path_label = tk.Label(master, text="当前库路径：未选择", wraplength=350)
        # self.lib_path_label.pack(pady=10)

        # self.select_lib_btn = tk.Button(
        #     master,
        #     text="选择库文件夹",
        #     command=self.select_library_folder,
        #     width=20
        # )
        # self.select_lib_btn.pack(pady=5)

        # 更新库按钮
        self.update_btn = tk.Button(
            master,
            text="更新库",
            command=self.update_library,
            width=20,
            bg="#4CAF50",
            fg="white"
        )
        self.update_btn.pack(pady=20)

    def select_gif_folder(self):
        path = filedialog.askdirectory()
        if path:
            self.gif_folder_path = path
            self.gif_path_label.config(text=f"当前GIF路径：{path}（已加载）")

    # def select_library_folder(self):
    #     path = filedialog.askdirectory()
    #     if path:
    #         self.library_folder_path = path
    #         self.lib_path_label.config(text=f"当前库路径：{path}（已加载）")

    def update_library(self):
        # 检查路径是否已选择
        # if not self.gif_folder_path or not self.library_folder_path:
        if not self.gif_folder_path:
            messagebox.showerror("错误", "请先选择库文件夹")
            return

        try:
            # 更新.c文件 gif_frames.h文件
            process_folder(self.gif_folder_path)
            # 更新.cpp 和 .h文件
            update_file(self.gif_folder_path)
            print(f"正在使用以下路径更新库：\nGIF路径：{self.gif_folder_path}")

            messagebox.showinfo("成功", "库更新完成！")
        except Exception as e:
            messagebox.showerror("错误", f"更新失败：{str(e)}")


if __name__ == "__main__":
    root = tk.Tk()
    app = GIFManagerUI(root)
    root.mainloop()