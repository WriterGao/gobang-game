#!/bin/bash

echo "🚀 五子棋游戏构建脚本"
echo "=============================="

# 检查Qt安装
if ! command -v qmake &> /dev/null; then
    echo "❌ 未检测到Qt安装，请先安装Qt5"
    echo "📋 请参考 快速安装指南.md 进行安装"
    exit 1
fi

echo "✅ 检测到Qt安装: $(qmake --version | head -1)"

# 清理构建目录
echo "🧹 清理构建目录..."
rm -rf build

# 创建构建目录
echo "�� 创建构建目录..."
mkdir build
cd build

# 配置项目
echo "⚙️ 配置项目..."
if cmake ..; then
    echo "✅ 配置成功"
else
    echo "❌ 配置失败，尝试手动指定Qt路径..."
    echo "💡 如果Qt安装在 ~/Qt/，请运行："
    echo "   cmake -DCMAKE_PREFIX_PATH=~/Qt/5.15.2/clang_64 .."
    exit 1
fi

# 构建项目
echo "🔨 构建项目..."
if cmake --build .; then
    echo "✅ 构建成功！"
    echo ""
    echo "🎮 运行游戏："
    echo "   ./bin/Gobang"
    echo ""
    echo "📁 可执行文件位置: $(pwd)/bin/Gobang"
else
    echo "❌ 构建失败"
    exit 1
fi
