# Qt 安装指南

本项目需要Qt5开发环境才能构建。以下是不同平台的安装方式：

## macOS 安装

### 方法1：使用Homebrew（推荐）
```bash
# 安装Homebrew（如果尚未安装）
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# 安装Qt5
brew install qt@5

# 设置环境变量
echo 'export PATH="/usr/local/opt/qt@5/bin:$PATH"' >> ~/.zshrc
echo 'export CMAKE_PREFIX_PATH="/usr/local/opt/qt@5:$CMAKE_PREFIX_PATH"' >> ~/.zshrc
source ~/.zshrc
```

### 方法2：从官方网站下载
1. 访问 https://www.qt.io/download
2. 下载Qt Online Installer
3. 运行安装程序，选择Qt 5.15 LTS
4. 安装完成后设置环境变量

## Ubuntu/Debian 安装

```bash
# 更新包管理器
sudo apt update

# 安装Qt5开发包
sudo apt install qt5-default qtcreator qtbase5-dev qttools5-dev

# 安装额外的Qt模块
sudo apt install qtmultimedia5-dev
```

## CentOS/RHEL/Fedora 安装

```bash
# CentOS/RHEL
sudo yum install qt5-qtbase-devel qt5-qttools-devel qt5-qtmultimedia-devel

# Fedora
sudo dnf install qt5-qtbase-devel qt5-qttools-devel qt5-qtmultimedia-devel
```

## Windows 安装

### 方法1：使用Qt Online Installer（推荐）
1. 访问 https://www.qt.io/download
2. 下载Qt Online Installer
3. 运行安装程序，创建Qt账号
4. 选择安装Qt 5.15 LTS
5. 确保选择以下组件：
   - Qt 5.15.x
   - Qt Creator IDE
   - CMake
   - Ninja

### 方法2：使用vcpkg
```cmd
# 安装vcpkg
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat

# 安装Qt5
.\vcpkg install qt5:x64-windows
```

## 验证安装

安装完成后，可以通过以下命令验证Qt是否正确安装：

```bash
# 检查Qt版本
qmake --version

# 检查CMake能否找到Qt
cmake --version
```

## 构建项目

Qt安装完成后，可以构建项目：

```bash
# 创建构建目录
mkdir build
cd build

# 配置项目
cmake ..

# 构建项目
cmake --build .

# 运行游戏
./bin/Gobang  # Linux/macOS
# 或
.\bin\Gobang.exe  # Windows
```

## 故障排除

### CMake找不到Qt

如果CMake报错找不到Qt，尝试以下解决方案：

1. **设置CMAKE_PREFIX_PATH**：
```bash
cmake -DCMAKE_PREFIX_PATH=/path/to/qt5 ..
```

2. **手动指定Qt5_DIR**：
```bash
cmake -DQt5_DIR=/path/to/qt5/lib/cmake/Qt5 ..
```

3. **macOS Homebrew特定路径**：
```bash
cmake -DCMAKE_PREFIX_PATH=/usr/local/opt/qt@5 ..
```

### 常见Qt路径

- **macOS Homebrew**: `/usr/local/opt/qt@5`
- **macOS Qt官方安装**: `~/Qt/5.15.x/clang_64`
- **Ubuntu**: `/usr/lib/x86_64-linux-gnu/cmake/Qt5`
- **Windows Qt官方**: `C:\Qt\5.15.x\msvc2019_64`

### 环境变量设置

在 `~/.bashrc` 或 `~/.zshrc` 中添加：

```bash
# macOS Homebrew
export PATH="/usr/local/opt/qt@5/bin:$PATH"
export CMAKE_PREFIX_PATH="/usr/local/opt/qt@5:$CMAKE_PREFIX_PATH"

# Linux
export PATH="/usr/bin:$PATH"
export CMAKE_PREFIX_PATH="/usr/lib/x86_64-linux-gnu/cmake/Qt5:$CMAKE_PREFIX_PATH"
```

## IDE 支持

### Qt Creator
Qt Creator 是官方推荐的IDE，提供完整的Qt开发支持。

### Visual Studio Code
可以使用CMake Tools扩展来支持CMake项目。

### CLion
JetBrains CLion 对CMake和Qt项目有很好的支持。

如果仍有问题，请检查：
1. Qt版本是否为5.12或更高
2. CMake版本是否为3.16或更高
3. 编译器是否支持C++17 