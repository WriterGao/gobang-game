#!/bin/bash

# macOS打包脚本
set -e

echo "🍎 开始构建macOS版本..."

# 清理旧的构建
rm -rf build_macos
mkdir build_macos
cd build_macos

# 配置和构建
echo "⚙️ 配置项目..."
cmake -DCMAKE_BUILD_TYPE=Release ..

echo "🔨 编译项目..."
cmake --build . --config Release

echo "📦 创建应用程序包..."
# 创建应用程序bundle
cmake --install . --prefix .

# 使用macdeployqt部署Qt库
echo "🔧 部署Qt依赖..."
macdeployqt ./Gobang.app -verbose=2

# 修复动态库链接路径（解决崩溃问题）
echo "🔧 修复动态库链接路径..."
cd Gobang.app/Contents/MacOS

# 添加RPATH（解决"no LC_RPATH's found"错误）
install_name_tool -add_rpath @executable_path/../Frameworks Gobang
echo "  ✅ 已添加RPATH"

# 修复每个Qt库的链接路径
for lib in libQt5MultimediaWidgets libQt5Concurrent libQt5Widgets libQt5Multimedia libQt5Gui libQt5Network libQt5Core; do
  install_name_tool -change @rpath/${lib}.5.dylib @executable_path/../Frameworks/${lib}.5.dylib Gobang
  echo "  ✅ 已修复 ${lib}"
done
cd ../../..

# 创建DMG安装包
echo "💿 创建DMG安装包..."
cpack -G DragNDrop

# 移动安装包到项目根目录
if [ -f *.dmg ]; then
    mv *.dmg ../五子棋游戏-1.0.0-macOS.dmg
    echo "✅ macOS版本构建完成！"
    echo "📦 安装包：五子棋游戏-1.0.0-macOS.dmg"
else
    echo "❌ DMG创建失败"
    exit 1
fi

cd ..
