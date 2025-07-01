# 🔧 手动添加GitHub Actions指南

如果您不想重新创建token，可以直接在GitHub网站上手动添加Actions配置：

## 📋 步骤说明

### 1. 访问您的GitHub仓库
🔗 https://github.com/WriterGao/gobang-game

### 2. 创建Actions配置文件
1. 点击仓库页面顶部的 **"Actions"** 标签
2. 如果是第一次使用，点击 **"set up a workflow yourself"**
3. 或者点击 **"New workflow"** → **"set up a workflow yourself"**

### 3. 设置工作流文件
1. **文件名**: 将默认的 `main.yml` 改为 `build.yml`
2. **文件路径**: 确认路径为 `.github/workflows/build.yml`
3. **文件内容**: 复制下面的完整配置

### 4. 复制以下配置内容
```yaml
name: 构建五子棋游戏

on:
  push:
    branches: [ main, master ]
  pull_request:
    branches: [ main, master ]
  release:
    types: [ published ]

jobs:
  build-windows:
    name: 构建Windows版本
    runs-on: windows-latest
    
    steps:
    - uses: actions/checkout@v3
    
    - name: 安装Qt
      uses: jurplel/install-qt-action@v3
      with:
        version: '5.15.2'
        arch: 'win64_msvc2019_64'
        
    - name: 配置MSVC
      uses: ilammy/msvc-dev-cmd@v1
      
    - name: 配置项目
      run: |
        mkdir build
        cd build
        cmake -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 16 2019" -A x64 ..
        
    - name: 编译项目
      run: |
        cd build
        cmake --build . --config Release
        
    - name: 部署Qt依赖
      run: |
        cd build
        cmake --install . --prefix . --config Release
        windeployqt.exe bin\Gobang.exe
        
    - name: 创建安装包
      run: |
        cd build
        cpack -G NSIS -C Release
        
    - name: 上传构建产物
      uses: actions/upload-artifact@v3
      with:
        name: 五子棋游戏-Windows
        path: build/*.exe

  build-macos:
    name: 构建macOS版本
    runs-on: macos-latest
    
    steps:
    - uses: actions/checkout@v3
    
    - name: 安装Qt
      uses: jurplel/install-qt-action@v3
      with:
        version: '5.15.2'
        
    - name: 配置项目
      run: |
        mkdir build
        cd build
        cmake -DCMAKE_BUILD_TYPE=Release ..
        
    - name: 编译项目
      run: |
        cd build
        cmake --build . --config Release
        
    - name: 创建应用程序包
      run: |
        cd build
        cmake --install . --prefix .
        macdeployqt ./Gobang.app -verbose=2
        
    - name: 创建DMG
      run: |
        cd build
        cpack -G DragNDrop
        
    - name: 上传构建产物
      uses: actions/upload-artifact@v3
      with:
        name: 五子棋游戏-macOS
        path: build/*.dmg

  build-linux:
    name: 构建Linux版本
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v3
    
    - name: 安装系统依赖
      run: |
        sudo apt-get update
        sudo apt-get install -y qt5-default qtmultimedia5-dev cmake build-essential
        
    - name: 配置项目
      run: |
        mkdir build
        cd build
        cmake -DCMAKE_BUILD_TYPE=Release ..
        
    - name: 编译项目
      run: |
        cd build
        cmake --build . --config Release
        
    - name: 创建安装包
      run: |
        cd build
        cmake --install . --prefix .
        cpack -G DEB
        cpack -G TGZ
        
    - name: 上传构建产物
      uses: actions/upload-artifact@v3
      with:
        name: 五子棋游戏-Linux
        path: |
          build/*.deb
          build/*.tar.gz

  release:
    name: 发布版本
    needs: [build-windows, build-macos, build-linux]
    runs-on: ubuntu-latest
    if: github.event_name == 'release'
    
    steps:
    - name: 下载所有构建产物
      uses: actions/download-artifact@v3
      
    - name: 上传到Release
      uses: softprops/action-gh-release@v1
      with:
        files: |
          五子棋游戏-Windows/*
          五子棋游戏-macOS/*
          五子棋游戏-Linux/*
      env:
        GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
```

### 5. 提交配置
1. 点击页面右上角的 **"Commit changes..."**
2. 填写提交信息：`添加自动构建配置`
3. 点击 **"Commit changes"**

### 6. 查看构建进度
🔗 https://github.com/WriterGao/gobang-game/actions

## ⏱️ 构建时间
- **Windows版本**: 约10-15分钟
- **macOS版本**: 约8-12分钟  
- **Linux版本**: 约5-8分钟

## 📦 下载构建产物
构建完成后，在Actions页面点击对应的构建任务，在页面底部的"Artifacts"部分可以下载安装包。 