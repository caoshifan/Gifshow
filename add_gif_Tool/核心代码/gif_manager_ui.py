"""
GIF库管理器图形界面
支持添加、删除、预览GIF动画
"""
import tkinter as tk
from tkinter import filedialog, messagebox, ttk
import os
from gif_manager import GifLibraryManager

class GifManagerUI:
    def __init__(self, master):
        self.master = master
        self.master.title("GIF动画库管理器 v2.0")
        self.master.geometry("700x600")
        self.master.resizable(True, True)
        
        # 初始化GIF管理器
        self.gif_manager = GifLibraryManager()
        
        # 创建界面
        self.create_widgets()
        
        # 初始加载和检查库状态
        self.check_library_status()

    def create_widgets(self):
        """创建界面组件"""
        # 主标题
        title_label = tk.Label(
            self.master, 
            text="GIF动画库管理器 v2.0", 
            font=("微软雅黑", 16, "bold"),
            fg="#2c3e50"
        )
        title_label.pack(pady=10)
        
        # 库状态框架
        status_frame = tk.LabelFrame(self.master, text="库状态", font=("微软雅黑", 10))
        status_frame.pack(fill=tk.X, padx=20, pady=(0, 10))
        
        # 库路径显示和选择
        path_frame = tk.Frame(status_frame)
        path_frame.pack(fill=tk.X, padx=10, pady=10)
        
        tk.Label(path_frame, text="库路径:", font=("微软雅黑", 9)).pack(side=tk.LEFT)
        
        self.library_path_var = tk.StringVar(value="未设置")
        path_display = tk.Label(
            path_frame, 
            textvariable=self.library_path_var, 
            bg="#f8f9fa",
            relief=tk.SUNKEN,
            padx=5,
            pady=2,
            anchor=tk.W,
            font=("Consolas", 8)
        )
        path_display.pack(side=tk.LEFT, fill=tk.X, expand=True, padx=(5, 5))
        
        tk.Button(
            path_frame,
            text="📁 选择库路径",
            command=self.select_library_path,
            bg="#3498db",
            fg="white",
            font=("微软雅黑", 8)
        ).pack(side=tk.RIGHT)
        
        # 库状态显示
        self.library_status_var = tk.StringVar(value="检查中...")
        self.library_status_label = tk.Label(
            status_frame,
            textvariable=self.library_status_var,
            font=("微软雅黑", 9),
            fg="#e67e22"
        )
        self.library_status_label.pack(pady=(0, 10))
        
        # 创建主框架
        main_frame = tk.Frame(self.master)
        main_frame.pack(fill=tk.BOTH, expand=True, padx=20, pady=10)
        
        # 左侧 - 现有GIF列表
        left_frame = tk.LabelFrame(main_frame, text="当前库中的GIF动画", font=("微软雅黑", 10))
        left_frame.pack(side=tk.LEFT, fill=tk.BOTH, expand=True, padx=(0, 10))
        
        # GIF列表
        list_frame = tk.Frame(left_frame)
        list_frame.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)
        
        self.gif_listbox = tk.Listbox(list_frame, font=("Consolas", 10))
        scrollbar = tk.Scrollbar(list_frame, orient=tk.VERTICAL, command=self.gif_listbox.yview)
        self.gif_listbox.config(yscrollcommand=scrollbar.set)
        
        self.gif_listbox.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
        
        # 绑定双击事件
        self.gif_listbox.bind('<Double-1>', self.on_gif_double_click)
        
        # 列表操作按钮
        list_btn_frame = tk.Frame(left_frame)
        list_btn_frame.pack(fill=tk.X, padx=10, pady=(0, 10))
        
        tk.Button(
            list_btn_frame,
            text="🔄 刷新列表",
            command=self.refresh_gif_list,
            width=15,
            bg="#3498db",
            fg="white",
            font=("微软雅黑", 9)
        ).pack(side=tk.LEFT, padx=(0, 5))
        
        tk.Button(
            list_btn_frame,
            text="🗑️ 删除选中",
            command=self.delete_selected_gif,
            width=15,
            bg="#e74c3c",
            fg="white",
            font=("微软雅黑", 9)
        ).pack(side=tk.LEFT)
        
        # 右侧 - 操作面板
        right_frame = tk.LabelFrame(main_frame, text="操作面板", font=("微软雅黑", 10))
        right_frame.pack(side=tk.RIGHT, fill=tk.Y, padx=(10, 0))
        
        # 添加GIF部分
        add_frame = tk.LabelFrame(right_frame, text="添加新GIF", font=("微软雅黑", 9))
        add_frame.pack(fill=tk.X, padx=10, pady=10)
        
        # 选择的GIF路径显示
        self.gif_path_var = tk.StringVar(value="未选择文件夹")
        path_label = tk.Label(
            add_frame, 
            textvariable=self.gif_path_var, 
            wraplength=200,
            justify=tk.LEFT,
            bg="#ecf0f1",
            relief=tk.SUNKEN,
            padx=5,
            pady=5
        )
        path_label.pack(fill=tk.X, padx=10, pady=(10, 5))
        
        tk.Button(
            add_frame,
            text="📁 选择GIF文件夹",
            command=self.select_gif_folder,
            width=20,
            bg="#2ecc71",
            fg="white",
            font=("微软雅黑", 9)
        ).pack(pady=5)
        
        tk.Button(
            add_frame,
            text="➕ 添加到库",
            command=self.add_gif_to_library,
            width=20,
            bg="#27ae60",
            fg="white",
            font=("微软雅黑", 9, "bold")
        ).pack(pady=5)
        
        # 分隔线
        separator = ttk.Separator(right_frame, orient='horizontal')
        separator.pack(fill=tk.X, padx=10, pady=20)
        
        # 库管理部分
        manage_frame = tk.LabelFrame(right_frame, text="库管理", font=("微软雅黑", 9))
        manage_frame.pack(fill=tk.X, padx=10, pady=10)
        
        tk.Button(
            manage_frame,
            text="🔧 重建库文件",
            command=self.rebuild_library,
            width=20,
            bg="#f39c12",
            fg="white",
            font=("微软雅黑", 9)
        ).pack(pady=5)
        
        tk.Button(
            manage_frame,
            text="📦 打包库文件",
            command=self.package_library,
            width=20,
            bg="#9b59b6",
            fg="white",
            font=("微软雅黑", 9)
        ).pack(pady=5)
        
        # 帮助按钮
        tk.Button(
            manage_frame,
            text="❓ 使用帮助",
            command=self.show_help,
            width=20,
            bg="#95a5a6",
            fg="white",
            font=("微软雅黑", 9)
        ).pack(pady=5)
        
        # 状态栏
        self.status_var = tk.StringVar(value="就绪")
        status_bar = tk.Label(
            self.master, 
            textvariable=self.status_var, 
            relief=tk.SUNKEN, 
            anchor=tk.W,
            bg="#34495e",
            fg="white",
            font=("微软雅黑", 9)
        )
        status_bar.pack(side=tk.BOTTOM, fill=tk.X)

    def check_library_status(self):
        """检查并更新库状态"""
        try:
            status = self.gif_manager.get_library_status()
            
            if status["valid"]:
                self.library_path_var.set(status["path"])
                self.library_status_var.set(f"✅ {status['message']}")
                self.library_status_label.config(fg="#27ae60")
                self.refresh_gif_list()
            else:
                self.library_path_var.set(status["path"] or "未设置")
                self.library_status_var.set(f"❌ {status['message']}")
                self.library_status_label.config(fg="#e74c3c")
                # 清空列表
                self.gif_listbox.delete(0, tk.END)
                
                # 如果路径未设置，显示帮助信息
                if not status["path"]:
                    self.show_path_setup_help()
                    
        except Exception as e:
            self.library_status_var.set(f"❌ 检查状态时出错: {str(e)}")
            self.library_status_label.config(fg="#e74c3c")

    def select_library_path(self):
        """选择库路径"""
        folder_path = filedialog.askdirectory(
            title="选择MyLibrary文件夹",
            initialdir=os.getcwd()
        )
        
        if folder_path:
            success = self.gif_manager.set_library_path(folder_path)
            if success:
                messagebox.showinfo("成功", f"库路径设置成功!\n路径: {folder_path}")
                self.check_library_status()
            else:
                messagebox.showerror("错误", f"设置库路径失败!\n请确保选择的是正确的MyLibrary文件夹。\n\n选择的路径: {folder_path}")

    def show_path_setup_help(self):
        """显示路径设置帮助"""
        help_text = """
🔍 未找到库路径！

请点击 "📁 选择库路径" 按钮，选择你的 MyLibrary 文件夹。

📁 正确的文件夹结构应该是：
MyLibrary/
├── src/
│   ├── frames/          ← GIF文件夹
│   ├── MyLibrary.cpp    ← C++源文件
│   ├── MyLibrary.h      ← 头文件
│   └── gif_frames.h     ← GIF声明文件
├── examples/
└── library.properties

💡 提示：
• 确保选择的是 MyLibrary 文件夹本身
• 不是 frames 文件夹或其他子文件夹
• 如果从 dist 文件夹运行，需要手动指定路径
        """
        
        # 创建帮助窗口
        help_window = tk.Toplevel(self.master)
        help_window.title("库路径设置帮助")
        help_window.geometry("500x400")
        help_window.resizable(False, False)
        
        # 设置窗口居中
        help_window.transient(self.master)
        help_window.grab_set()
        
        # 帮助文本
        text_widget = tk.Text(
            help_window, 
            wrap=tk.WORD, 
            padx=20, 
            pady=20,
            font=("微软雅黑", 10),
            bg="#f8f9fa"
        )
        text_widget.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)
        text_widget.insert(tk.END, help_text)
        text_widget.config(state=tk.DISABLED)
        
        # 按钮框架
        btn_frame = tk.Frame(help_window)
        btn_frame.pack(pady=10)
        
        tk.Button(
            btn_frame,
            text="📁 选择库路径",
            command=lambda: [help_window.destroy(), self.select_library_path()],
            bg="#3498db",
            fg="white",
            font=("微软雅黑", 10),
            padx=20
        ).pack(side=tk.LEFT, padx=5)
        
        tk.Button(
            btn_frame,
            text="关闭",
            command=help_window.destroy,
            bg="#95a5a6",
            fg="white",
            font=("微软雅黑", 10),
            padx=20
        ).pack(side=tk.LEFT, padx=5)

    def refresh_gif_list(self):
        """刷新GIF列表"""
        try:
            self.gif_listbox.delete(0, tk.END)
            
            if not self.gif_manager.is_library_path_valid():
                self.status_var.set("❌ 库路径无效，无法加载GIF列表")
                return
            
            existing_gifs = self.gif_manager.get_existing_gifs()
            
            for gif_name in existing_gifs:
                self.gif_listbox.insert(tk.END, gif_name)
            
            self.status_var.set(f"已加载 {len(existing_gifs)} 个GIF动画")
            
        except Exception as e:
            messagebox.showerror("错误", f"刷新列表失败: {str(e)}")
            self.status_var.set("刷新列表失败")

    def select_gif_folder(self):
        """选择GIF文件夹"""
        if not self.gif_manager.is_library_path_valid():
            messagebox.showwarning("警告", "请先设置正确的库路径！")
            self.select_library_path()
            return
        
        folder_path = filedialog.askdirectory(
            title="选择包含.c文件的GIF文件夹",
            initialdir=os.getcwd()
        )
        
        if folder_path:
            # 检查文件夹是否包含.c文件
            c_files = [f for f in os.listdir(folder_path) if f.endswith('.c')]
            if not c_files:
                messagebox.showwarning("警告", "所选文件夹中没有找到.c文件！")
                return
            
            self.selected_gif_path = folder_path
            folder_name = os.path.basename(folder_path)
            self.gif_path_var.set(f"已选择: {folder_name}\n({len(c_files)} 个.c文件)")
            
            self.status_var.set(f"已选择文件夹: {folder_name}")

    def add_gif_to_library(self):
        """添加GIF到库"""
        if not self.gif_manager.is_library_path_valid():
            messagebox.showwarning("警告", "请先设置正确的库路径！")
            self.select_library_path()
            return
        
        if not hasattr(self, 'selected_gif_path'):
            messagebox.showwarning("警告", "请先选择GIF文件夹！")
            return
        
        # 确认添加
        gif_name = os.path.basename(self.selected_gif_path)
        if messagebox.askyesno("确认", f"确定要添加 '{gif_name}' 到库中吗？"):
            try:
                self.status_var.set("正在添加GIF...")
                self.master.update()
                
                success = self.gif_manager.add_gif(self.selected_gif_path)
                
                if success:
                    messagebox.showinfo("成功", f"成功添加GIF: {gif_name}")
                    self.refresh_gif_list()
                    self.check_library_status()
                    self.gif_path_var.set("未选择文件夹")
                    if hasattr(self, 'selected_gif_path'):
                        delattr(self, 'selected_gif_path')
                else:
                    messagebox.showerror("失败", f"添加GIF失败，请检查控制台日志")
                
                self.status_var.set("就绪")
                
            except Exception as e:
                messagebox.showerror("错误", f"添加GIF时出错: {str(e)}")
                self.status_var.set("就绪")

    def delete_selected_gif(self):
        """删除选中的GIF"""
        if not self.gif_manager.is_library_path_valid():
            messagebox.showwarning("警告", "请先设置正确的库路径！")
            self.select_library_path()
            return
        
        selection = self.gif_listbox.curselection()
        if not selection:
            messagebox.showwarning("警告", "请先选择要删除的GIF！")
            return
        
        gif_name = self.gif_listbox.get(selection[0])
        
        # 确认删除
        if messagebox.askyesno("确认删除", f"确定要删除 '{gif_name}' 吗？\n\n这将删除所有相关文件和代码，此操作不可撤销！"):
            try:
                self.status_var.set("正在删除GIF...")
                self.master.update()
                
                success = self.gif_manager.remove_gif(gif_name)
                
                if success:
                    messagebox.showinfo("成功", f"成功删除GIF: {gif_name}")
                    self.refresh_gif_list()
                    self.check_library_status()
                else:
                    messagebox.showerror("失败", f"删除GIF失败，请检查控制台日志")
                
                self.status_var.set("就绪")
                
            except Exception as e:
                messagebox.showerror("错误", f"删除GIF时出错: {str(e)}")
                self.status_var.set("就绪")

    def on_gif_double_click(self, event):
        """双击GIF项目时的处理"""
        selection = self.gif_listbox.curselection()
        if selection:
            gif_name = self.gif_listbox.get(selection[0])
            # 显示GIF信息
            self.show_gif_info(gif_name)

    def show_gif_info(self, gif_name):
        """显示GIF信息"""
        try:
            gif_dir = self.gif_manager.frames_dir / gif_name
            if gif_dir.exists():
                c_files = list(gif_dir.glob("*.c"))
                info = f"GIF名称: {gif_name}\n"
                info += f"帧数: {len(c_files)}\n"
                info += f"路径: {gif_dir}\n"
                info += f"文件大小: {sum(f.stat().st_size for f in c_files) / 1024:.2f} KB"
                
                messagebox.showinfo(f"GIF信息 - {gif_name}", info)
            else:
                messagebox.showerror("错误", f"找不到GIF文件夹: {gif_name}")
        except Exception as e:
            messagebox.showerror("错误", f"获取GIF信息失败: {str(e)}")

    def rebuild_library(self):
        """重建库文件"""
        if not self.gif_manager.is_library_path_valid():
            messagebox.showwarning("警告", "请先设置正确的库路径！")
            self.select_library_path()
            return
        
        if messagebox.askyesno("确认", "确定要重建库文件吗？\n\n这将重新生成所有库文件。"):
            try:
                self.status_var.set("正在重建库...")
                self.master.update()
                
                success = self.gif_manager.rebuild_library()
                
                if success:
                    messagebox.showinfo("成功", "库文件重建完成！")
                    self.refresh_gif_list()
                    self.check_library_status()
                else:
                    messagebox.showerror("失败", "重建库文件失败!")
                
                self.status_var.set("就绪")
                
            except Exception as e:
                messagebox.showerror("错误", f"重建库失败: {str(e)}")
                self.status_var.set("就绪")

    def package_library(self):
        """打包库文件为zip"""
        if not self.gif_manager.is_library_path_valid():
            messagebox.showwarning("警告", "请先设置正确的库路径！")
            self.select_library_path()
            return
        
        try:
            import zipfile
            from datetime import datetime
            
            # 选择保存位置
            zip_path = filedialog.asksaveasfilename(
                title="保存库文件",
                defaultextension=".zip",
                filetypes=[("ZIP文件", "*.zip")],
                initialname=f"MyLibrary_{datetime.now().strftime('%Y%m%d_%H%M%S')}.zip"
            )
            
            if zip_path:
                self.status_var.set("正在打包库文件...")
                self.master.update()
                
                with zipfile.ZipFile(zip_path, 'w', zipfile.ZIP_DEFLATED) as zipf:
                    # 遍历MyLibrary目录中的所有文件
                    library_root = self.gif_manager.library_root
                    for root, dirs, files in os.walk(library_root):
                        for file in files:
                            file_path = os.path.join(root, file)
                            arcname = os.path.relpath(file_path, library_root.parent)
                            zipf.write(file_path, arcname)
                
                messagebox.showinfo("成功", f"库文件已打包到: {zip_path}")
                self.status_var.set("就绪")
                
        except Exception as e:
            messagebox.showerror("错误", f"打包失败: {str(e)}")
            self.status_var.set("就绪")

    def show_help(self):
        """显示使用帮助"""
        help_text = """
🎯 GIF动画库管理器 v2.0 使用帮助

📋 主要功能：
• 📁 添加GIF - 将.c文件添加到库中
• 🗑️ 删除GIF - 从库中移除动画
• 📊 可视化管理 - 查看所有GIF列表
• 🔧 库维护 - 重建、打包功能

🚀 使用步骤：
1. 设置库路径 - 点击"选择库路径"按钮
2. 查看GIF列表 - 左侧显示所有现有动画
3. 添加新GIF - 选择.c文件夹后添加
4. 管理现有GIF - 删除、查看信息

⚠️ 重要提示：
• 确保库路径指向正确的MyLibrary文件夹
• 删除操作不可撤销，请谨慎操作
• .c文件需要标准的数组格式
• 重要操作前建议备份数据

❓ 常见问题：
• 如果列表为空，请检查库路径设置
• 如果添加失败，检查.c文件格式
• 如果删除不完整，使用"重建库文件"

📞 需要帮助？请查看README_v2.md文档
        """
        
        # 创建帮助窗口
        help_window = tk.Toplevel(self.master)
        help_window.title("使用帮助")
        help_window.geometry("500x500")
        help_window.resizable(False, False)
        
        # 设置窗口居中
        help_window.transient(self.master)
        help_window.grab_set()
        
        # 帮助文本
        text_widget = tk.Text(
            help_window, 
            wrap=tk.WORD, 
            padx=20, 
            pady=20,
            font=("微软雅黑", 10),
            bg="#f8f9fa"
        )
        text_widget.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)
        text_widget.insert(tk.END, help_text)
        text_widget.config(state=tk.DISABLED)
        
        # 关闭按钮
        tk.Button(
            help_window,
            text="关闭",
            command=help_window.destroy,
            bg="#95a5a6",
            fg="white",
            font=("微软雅黑", 10),
            padx=20
        ).pack(pady=10)


def main():
    root = tk.Tk()
    app = GifManagerUI(root)
    root.mainloop()


if __name__ == "__main__":
    main() 