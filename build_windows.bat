@echo off
REM Windows打包脚本

echo 🪟 开始构建Windows版本...

REM 清理旧的构建
if exist build_windows rmdir /s /q build_windows
mkdir build_windows
cd build_windows

echo ⚙️ 配置项目...
cmake -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 16 2019" -A x64 ..

echo 🔨 编译项目...
cmake --build . --config Release

echo 📦 安装到本地目录...
cmake --install . --prefix . --config Release

echo 🔧 部署Qt依赖...
REM 使用windeployqt部署Qt库
windeployqt.exe bin\Gobang.exe --qmldir ..\src

echo 💿 创建安装包...
cpack -G NSIS -C Release

REM 移动安装包到项目根目录
if exist *.exe (
    move *.exe ..\五子棋游戏-1.0.0-Windows.exe
    echo ✅ Windows版本构建完成！
    echo 📦 安装包：五子棋游戏-1.0.0-Windows.exe
) else (
    echo ❌ 安装包创建失败
    exit /b 1
)

cd ..
pause
