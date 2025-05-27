@echo off
echo.
echo ====================================
echo    GIF动画库管理器 v2.0
echo ====================================
echo.
echo 正在启动程序...
echo.

REM 切换到当前目录
cd /d "%~dp0"

REM 启动程序
start "" "dist\GifManager_v2.exe"

echo 程序已启动！
echo.
echo 如果程序没有正常启动，请检查：
echo 1. 是否在项目根目录运行
echo 2. MyLibrary文件夹是否存在
echo 3. 直接双击 dist\GifManager_v2.exe 运行
echo.
pause 