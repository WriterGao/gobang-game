@echo off
chcp 65001
echo ========================================
echo     五子棋游戏 Qt库文件获取助手
echo ========================================
echo.

echo 正在检查当前目录...
if not exist "bin\Gobang.exe" (
    echo 错误：请将此脚本放在包含bin目录的游戏文件夹中！
    echo 当前目录应该包含：bin\Gobang.exe
    pause
    exit /b 1
)

echo 找到游戏可执行文件：bin\Gobang.exe
echo.

echo 检查所需的Qt库文件...
set MISSING_FILES=0

if not exist "bin\Qt5Core.dll" (
    echo [缺失] Qt5Core.dll
    set /a MISSING_FILES+=1
)

if not exist "bin\Qt5Gui.dll" (
    echo [缺失] Qt5Gui.dll
    set /a MISSING_FILES+=1
)

if not exist "bin\Qt5Widgets.dll" (
    echo [缺失] Qt5Widgets.dll
    set /a MISSING_FILES+=1
)

if not exist "bin\Qt5Multimedia.dll" (
    echo [缺失] Qt5Multimedia.dll
    set /a MISSING_FILES+=1
)

if %MISSING_FILES%==0 (
    echo ✅ 所有Qt库文件都已存在！
    echo 您可以直接运行 bin\Gobang.exe
    pause
    exit /b 0
)

echo.
echo 需要获取 %MISSING_FILES% 个Qt库文件
echo.

echo ========================================
echo     选择获取方式
echo ========================================
echo.
echo 1. 自动搜索系统中已安装的Qt
echo 2. 打开官方Qt下载页面
echo 3. 打开在线DLL下载站点
echo 4. 显示手动获取说明
echo 5. 退出
echo.

set /p choice=请选择 (1-5): 

if "%choice%"=="1" goto :search_qt
if "%choice%"=="2" goto :open_qt_official
if "%choice%"=="3" goto :open_dll_sites
if "%choice%"=="4" goto :manual_guide
if "%choice%"=="5" goto :end

echo 无效选择，请重新运行脚本
goto :end

:search_qt
echo.
echo 正在搜索系统中的Qt安装...
echo.

rem 搜索常见的Qt安装路径
set QT_FOUND=0
for %%d in (C D E F) do (
    if exist "%%d:\Qt\5.15.2\msvc2019_64\bin\Qt5Core.dll" (
        echo 找到Qt安装：%%d:\Qt\5.15.2\msvc2019_64\
        set QT_PATH=%%d:\Qt\5.15.2\msvc2019_64
        set QT_FOUND=1
        goto :copy_qt_files
    )
)

if exist "C:\Qt\Qt5.15.2\5.15.2\msvc2019_64\bin\Qt5Core.dll" (
    echo 找到Qt安装：C:\Qt\Qt5.15.2\5.15.2\msvc2019_64\
    set QT_PATH=C:\Qt\Qt5.15.2\5.15.2\msvc2019_64
    set QT_FOUND=1
    goto :copy_qt_files
)

if %QT_FOUND%==0 (
    echo ❌ 未找到Qt安装
    echo 请选择其他方式获取Qt库文件
    echo.
    pause
    goto :end
)

:copy_qt_files
echo.
echo 正在复制Qt库文件...

if not exist "bin\Qt5Core.dll" (
    if exist "%QT_PATH%\bin\Qt5Core.dll" (
        copy "%QT_PATH%\bin\Qt5Core.dll" "bin\" >nul 2>&1
        if errorlevel 1 (
            echo ❌ 复制Qt5Core.dll失败
        ) else (
            echo ✅ 复制Qt5Core.dll成功
        )
    )
)

if not exist "bin\Qt5Gui.dll" (
    if exist "%QT_PATH%\bin\Qt5Gui.dll" (
        copy "%QT_PATH%\bin\Qt5Gui.dll" "bin\" >nul 2>&1
        if errorlevel 1 (
            echo ❌ 复制Qt5Gui.dll失败
        ) else (
            echo ✅ 复制Qt5Gui.dll成功
        )
    )
)

if not exist "bin\Qt5Widgets.dll" (
    if exist "%QT_PATH%\bin\Qt5Widgets.dll" (
        copy "%QT_PATH%\bin\Qt5Widgets.dll" "bin\" >nul 2>&1
        if errorlevel 1 (
            echo ❌ 复制Qt5Widgets.dll失败
        ) else (
            echo ✅ 复制Qt5Widgets.dll成功
        )
    )
)

if not exist "bin\Qt5Multimedia.dll" (
    if exist "%QT_PATH%\bin\Qt5Multimedia.dll" (
        copy "%QT_PATH%\bin\Qt5Multimedia.dll" "bin\" >nul 2>&1
        if errorlevel 1 (
            echo ❌ 复制Qt5Multimedia.dll失败
        ) else (
            echo ✅ 复制Qt5Multimedia.dll成功
        )
    )
)

rem 复制平台插件
if not exist "bin\platforms" mkdir "bin\platforms"
if exist "%QT_PATH%\plugins\platforms\qwindows.dll" (
    copy "%QT_PATH%\plugins\platforms\qwindows.dll" "bin\platforms\" >nul 2>&1
    if errorlevel 1 (
        echo ❌ 复制qwindows.dll失败
    ) else (
        echo ✅ 复制qwindows.dll成功
    )
)

echo.
echo 复制完成！尝试运行游戏...
echo.
set /p run_game=是否现在运行游戏？(y/n): 
if /i "%run_game%"=="y" (
    start "五子棋游戏" "bin\Gobang.exe"
)
goto :end

:open_qt_official
echo.
echo 正在打开Qt官方下载页面...
start https://www.qt.io/download-open-source
echo.
echo 请在官方页面下载并安装Qt 5.15.2
echo 安装后重新运行此脚本选择选项1
pause
goto :end

:open_dll_sites
echo.
echo 正在打开DLL下载站点...
echo 请下载以下文件的64位版本：
echo.
start https://www.dll-files.com/qt5core.dll.html
timeout /t 2 >nul
start https://www.dll-files.com/qt5gui.dll.html
timeout /t 2 >nul
start https://www.dll-files.com/qt5widgets.dll.html
timeout /t 2 >nul
start https://www.dll-files.com/qt5multimedia.dll.html

echo.
echo 下载完成后，请将DLL文件复制到bin目录
echo 然后运行此脚本检查是否完整
pause
goto :end

:manual_guide
echo.
echo ========================================
echo         手动获取Qt库文件指南
echo ========================================
echo.
echo 需要获取的文件：
echo   Qt5Core.dll
echo   Qt5Gui.dll  
echo   Qt5Widgets.dll
echo   Qt5Multimedia.dll
echo   qwindows.dll (平台插件)
echo.
echo 获取方式：
echo.
echo 方式1 - 从Qt安装目录复制：
echo   从 C:\Qt\5.15.2\msvc2019_64\bin\ 复制前4个文件
echo   从 C:\Qt\5.15.2\msvc2019_64\plugins\platforms\ 复制qwindows.dll
echo.
echo 方式2 - 在线下载：
echo   访问 dll-files.com 搜索并下载各个DLL文件
echo   确保下载64位版本
echo.
echo 方式3 - 安装Qt运行时：
echo   访问 https://www.qt.io/download
echo   安装Qt 5.15.2 MSVC 2019 64位版本
echo.
echo 部署位置：
echo   将前4个DLL复制到 bin\ 目录
echo   在bin目录创建platforms文件夹
echo   将qwindows.dll复制到 bin\platforms\ 目录
echo.
pause
goto :end

:end
echo.
echo 脚本结束。祝您游戏愉快！
pause 