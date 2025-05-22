# DocStudio

[English](#english) | [中文](#中文)

## English

### Overview

This is an Arduino library for playing GIFs on the ssd1306 display. The library includes a tool to add pre-processed GIF images. After adding, just compress and import it into Arduino.

### Main File Structure

- **add_gif_Tool**:Contains the source code and the packed .exe file of the adding tool, which is Python - based
    - **add_gif_Tool/dist**: The packed .exe file
- **MyLibrary**: The Arduino library
    - **MyLibrary/src**: The specific implementation
        - **MyLibrary/src/frames**: Stores the .c array files of the pre-processed GIF images

### Usage

1. Decompose the GIF animation (Gifsplitter is recommended)
2. Image halftoning (Img2Lcd is recommended for batch conversion)
    - **Parameter settings for reference**
        1.Output: C array(C语言数组)
        2.Scan mode: Horizontal scan(水平扫描)
        3.Output grayscale: Monochrome(单色)
        4.Maximum width and height: 128*64
        5.No need to check the lower-left checkbox
3. Create a new folder named after your GIF in the MyLibrary/src/frames directory, and copy the halftoned .c files into it
4.Run the .exe or the win_ui.py file in the add_gif_Tool folder, click "选择GIF文件夹", navigate to the folder created in step 3, and then click Update Library("更新库")
5.Finally, compress the MyLibrary folder into a .zip file, import it into the Arduino library, and then replace the preset animation name with the new folder name (all in uppercase) in the example to use it


#### Future Features
- 🔄 Integrate decomposition and halftoning
- 🔄 Integrate compression

---

## 中文

### 概述

这是一个适用于ssd1306的GIF播放Arduino库，本库自带添加工具，可以将取模好的GIF图添加到库中。添加完后压缩导入Arduino即可。

### 文件结构

- **add_gif_Tool**：存放添加工具源码以及打包后的.exe文件，工具基于python实现
    - **add_gif_Tool/dist**：打包好的.exe文件
- **MyLibrary**：Adruino库
    - **MyLibrary/src**：具体实现方式
        - **MyLibrary/src/frames**：存放GIF取模后的.c数组文件

### 使用方法

1. GIF图动图分解（建议使用Gifsplitter）
2. 图像取模 （推荐使用Img2Lcd批量转换）
    - **参数设置参考**
        1.输出：C语言数组
        2.扫描模式：水平扫描
        3.输出灰度：单色
        4.最大宽度和高度128*64
        5.左侧下方勾选栏无需勾选
3. 在MyLibrary/src/frames目录下新建你需要的GIF图名的文件夹，将取模后的.c文件拷贝到该文件夹下
4.运行.exe或add_gif_Tool文件夹下win_ui.py文件，点击"选择GIF文件夹"，定位到点第3步建立的文件夹，然后点击更新库即可
5.最后将MyLibrary文件夹压缩为.zip文件，导入Adruino库即可，按照示例使用新建的文件夹名（全大写）替换预设动画名称即可使用


#### 未来功能
- 🔄 集成分解取模
- 🔄 集成压缩

Modification Log:
2025/4/21: 修改begin函数  begin函数传参rotation,参数用于display.setRotation(rotation)。默认值为-1，画满不做转换，传入2则画面旋转180°（上下颠倒）
2025/5/22: 增加turnOnScreen 以及 turnOffScreen 函数,用于控制显示屏开关。使用方式声明对象后 Mylibrary.turnOnScreen()即可。