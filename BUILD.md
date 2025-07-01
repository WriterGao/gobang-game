# 五子棋游戏 - 构建指南

## �� 概述

本项目支持在Windows、macOS和Linux平台上构建和运行。提供了完整的跨平台构建脚本和自动化构建流程。

## 🎯 快速开始

### 自动化构建（推荐）

```bash
# 运行通用构建脚本
./build_all.sh
```

### 手动构建

根据您的平台选择对应脚本：

- **macOS**: `./build_macos.sh`
- **Windows**: `build_windows.bat`
- **Linux**: `./build_linux.sh`

## 📦 构建产物

成功构建后，您将获得以下安装包：

- **macOS**: `五子棋游戏-1.0.0-macOS.dmg`
- **Windows**: `五子棋游戏-1.0.0-Windows.exe`
- **Linux**: `五子棋游戏-1.0.0-Linux-*.deb/rpm/tar.gz`

## 🔧 系统要求

### 🍎 macOS

- macOS 10.14+
- Xcode Command Line Tools
- Qt 5.15+ (推荐通过conda安装)
- CMake 3.16+

```bash
# 安装依赖（如果使用conda）
conda install qt cmake
```

### 🪟 Windows

- Windows 10+
- Visual Studio 2019+ (Community版本即可)
- Qt 5.15+ (从官网下载安装器)
- CMake 3.16+
- NSIS (用于创建安装包)

### 🐧 Linux

#### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install qt5-default qtmultimedia5-dev cmake build-essential
```

#### CentOS/RHEL
```bash
sudo yum install qt5-qtbase-devel qt5-qtmultimedia-devel cmake gcc-c++
```

#### Arch Linux
```bash
sudo pacman -S qt5-base qt5-multimedia cmake base-devel
```

## 🚀 GitHub Actions自动化构建

项目配置了GitHub Actions，可以自动构建所有平台版本：

1. 推送代码到GitHub
2. Actions自动触发构建
3. 在Actions页面下载构建产物
4. 创建Release时自动发布所有平台版本

## 🛠️ 高级构建选项

### 自定义构建类型

```bash
# Debug版本
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Release版本（默认）
cmake -DCMAKE_BUILD_TYPE=Release ..
```

### 指定Qt路径

```bash
# 如果Qt未在标准路径
cmake -DCMAKE_PREFIX_PATH=/path/to/qt ..
```

### 跨平台编译

使用Docker或虚拟机在单一平台构建多个目标平台。

## 📱 安装和运行

### macOS
1. 打开DMG文件
2. 将应用拖拽到Applications文件夹
3. 首次运行可能需要在"安全与隐私"中允许

### Windows
1. 运行EXE安装包
2. 按照向导完成安装
3. 从开始菜单启动游戏

### Linux
```bash
# DEB包（Ubuntu/Debian）
sudo dpkg -i 五子棋游戏-1.0.0-Linux-*.deb

# RPM包（CentOS/RHEL）
sudo rpm -i 五子棋游戏-1.0.0-Linux-*.rpm

# TAR.GZ包（通用）
tar -xzf 五子棋游戏-1.0.0-Linux-*.tar.gz
cd bin && ./Gobang
```

## 🐛 故障排除

### 常见问题

**Q: CMake找不到Qt**
```bash
# 设置Qt路径
export CMAKE_PREFIX_PATH=/path/to/qt
```

**Q: macOS上"应用已损坏"**
```bash
# 移除隔离属性
sudo xattr -r -d com.apple.quarantine /Applications/五子棋游戏.app
```

**Q: Linux上缺少依赖**
```bash
# 检查依赖
ldd ./Gobang
# 安装缺少的库
sudo apt-get install libqt5multimedia5
```

### 获取帮助

- 检查构建日志中的错误信息
- 确认所有依赖已正确安装
- 参考GitHub Issues中的解决方案

## 📝 开发者说明

### 项目结构
```
.
├── src/                 # 源代码
├── resources/           # 资源文件
├── build_*.sh          # 构建脚本
├── CMakeLists.txt      # CMake配置
├── Info.plist.in       # macOS应用信息
├── gobang.desktop      # Linux桌面文件
└── .github/workflows/  # GitHub Actions
```

### 添加新功能

1. 修改源代码
2. 更新CMakeLists.txt（如需要）
3. 测试所有平台构建
4. 更新版本号
5. 创建Release

---

🎮 享受您的五子棋游戏开发之旅！
