#!/bin/bash

# Linux打包脚本
set -e

echo "🐧 开始构建Linux版本..."

# 检查依赖
echo "📋 检查系统依赖..."
if ! command -v qmake &> /dev/null; then
    echo "❌ 错误：未找到Qt开发环境"
    echo "请安装Qt5开发包："
    echo "Ubuntu/Debian: sudo apt-get install qt5-default qtmultimedia5-dev"
    echo "CentOS/RHEL: sudo yum install qt5-qtbase-devel qt5-qtmultimedia-devel"
    echo "Arch Linux: sudo pacman -S qt5-base qt5-multimedia"
    exit 1
fi

# 清理旧的构建
rm -rf build_linux
mkdir build_linux
cd build_linux

# 配置和构建
echo "⚙️ 配置项目..."
cmake -DCMAKE_BUILD_TYPE=Release ..

echo "🔨 编译项目..."
cmake --build . --config Release

echo "📦 安装到本地目录..."
cmake --install . --prefix .

# 检查是否存在linuxdeployqt
if command -v linuxdeployqt &> /dev/null; then
    echo "🔧 使用linuxdeployqt部署依赖..."
    linuxdeployqt bin/Gobang -bundle-non-qt-libs
else
    echo "⚠️ 未找到linuxdeployqt，跳过依赖打包"
    echo "如需自包含版本，请安装linuxdeployqt"
fi

echo "💿 创建安装包..."
# 创建DEB包
cpack -G DEB
# 创建RPM包（如果可用）
if command -v rpmbuild &> /dev/null; then
    cpack -G RPM
fi
# 创建TAR.GZ包
cpack -G TGZ

# 移动安装包到项目根目录
echo "📦 整理安装包..."
for file in *.deb *.rpm *.tar.gz; do
    if [ -f "$file" ]; then
        base_name=$(basename "$file")
        mv "$file" "../五子棋游戏-1.0.0-Linux-$base_name"
    fi
done

echo "✅ Linux版本构建完成！"
echo "📦 安装包列表："
ls -la ../五子棋游戏-1.0.0-Linux-* 2>/dev/null || echo "未生成安装包文件"

cd ..
