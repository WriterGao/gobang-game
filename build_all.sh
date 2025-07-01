#!/bin/bash

# 全平台打包脚本
set -e

echo "🚀 五子棋游戏 - 全平台打包工具"
echo "================================"

# 检测当前平台
if [[ "$OSTYPE" == "darwin"* ]]; then
    CURRENT_OS="macOS"
elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
    CURRENT_OS="Linux"
elif [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "cygwin" ]]; then
    CURRENT_OS="Windows"
else
    echo "❌ 不支持的操作系统: $OSTYPE"
    exit 1
fi

echo "当前平台: $CURRENT_OS"
echo ""

# 显示菜单
echo "请选择要构建的平台："
echo "1) 仅构建当前平台 ($CURRENT_OS)"
echo "2) 构建所有平台 (需要跨平台环境)"
echo "3) 显示构建说明"
echo "4) 退出"
echo ""

read -p "请输入选择 (1-4): " choice

case $choice in
    1)
        echo "🔨 构建当前平台: $CURRENT_OS"
        if [[ "$CURRENT_OS" == "macOS" ]]; then
            bash build_macos.sh
        elif [[ "$CURRENT_OS" == "Linux" ]]; then
            bash build_linux.sh
        elif [[ "$CURRENT_OS" == "Windows" ]]; then
            cmd //c build_windows.bat
        fi
        ;;
    2)
        echo "🌍 构建所有平台..."
        echo "注意：这需要配置跨平台编译环境"
        
        if [[ "$CURRENT_OS" == "macOS" ]]; then
            echo "构建macOS版本..."
            bash build_macos.sh
        fi
        
        echo "ℹ️ 要构建其他平台，请在相应系统上运行对应脚本"
        echo "Windows: build_windows.bat"
        echo "Linux: build_linux.sh"
        ;;
    3)
        cat << 'INSTRUCTIONS'

📚 构建说明
===========

📋 系统要求：

🍎 macOS:
- macOS 10.14+
- Xcode Command Line Tools
- Qt 5.15+ (通过conda或官方安装)
- CMake 3.16+

🪟 Windows:
- Windows 10+
- Visual Studio 2019+ 
- Qt 5.15+ (官方安装器)
- CMake 3.16+
- NSIS (用于创建安装包)

🐧 Linux:
- Ubuntu 18.04+ / CentOS 7+ / Arch Linux
- Qt5开发包: qt5-default qtmultimedia5-dev
- CMake 3.16+
- 可选：linuxdeployqt (用于依赖打包)

🔧 构建步骤：

1. 确保安装了所需依赖
2. 在对应平台运行对应脚本：
   - macOS: ./build_macos.sh
   - Windows: build_windows.bat
   - Linux: ./build_linux.sh

�� 输出文件：
- macOS: 五子棋游戏-1.0.0-macOS.dmg
- Windows: 五子棋游戏-1.0.0-Windows.exe
- Linux: 五子棋游戏-1.0.0-Linux-*.deb/rpm/tar.gz

INSTRUCTIONS
        ;;
    4)
        echo "👋 再见！"
        exit 0
        ;;
    *)
        echo "❌ 无效选择"
        exit 1
        ;;
esac

echo ""
echo "✅ 构建完成！"
echo "📦 查看生成的安装包文件"
