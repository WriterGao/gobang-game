# Windows版本构建指南

## 🌟 方案1：GitHub Actions自动构建（推荐）

### 步骤：
1. **推送代码到GitHub**：
   ```bash
   git add .
   git commit -m "准备Windows构建"
   git push origin main
   ```

2. **查看Actions页面**：
   - 访问：https://github.com/your-repo/actions
   - 等待构建完成（约10-15分钟）
   - 下载Windows构建产物

3. **获取安装包**：
   - 在Actions运行完成后
   - 点击对应的workflow
   - 下载"五子棋游戏-Windows"artifact
   - 解压得到.exe安装包

## 🖥️ 方案2：本地Windows环境构建

### 在Windows机器上：
1. **安装依赖**：
   - Visual Studio 2019+ Community
   - Qt 5.15.2 (从qt.io下载)
   - CMake 3.16+
   - NSIS (创建安装包)

2. **运行构建**：
   ```cmd
   # 下载项目代码
   git clone <项目地址>
   cd 五子棋
   
   # 运行Windows构建脚本
   build_windows.bat
   ```

3. **获取结果**：
   - 构建完成后获得：五子棋游戏-1.0.0-Windows.exe

## 🐳 方案3：Docker跨平台构建

### 使用Docker（实验性）：
```bash
# 构建Windows版本（需要特殊配置）
docker run --rm -v $(pwd):/workspace windows-qt-builder
```

## ⚡ 快速选择建议

- **有GitHub仓库** → 选择方案1（GitHub Actions）
- **有Windows电脑** → 选择方案2（本地构建）  
- **技术探索** → 选择方案3（Docker）

