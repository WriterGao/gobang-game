# 🪟 立即构建Windows版本 

## 🌟 最简单方案：GitHub Actions（推荐）

### 一键触发构建：
```bash
# 运行这个脚本即可自动触发GitHub构建
./trigger_windows_build.sh
```

### 手动触发（如果没有Git配置）：
1. **创建GitHub仓库**（如果还没有）
2. **上传项目代码**：
   ```bash
   git init
   git add .
   git commit -m "五子棋游戏项目"
   git remote add origin https://github.com/你的用户名/仓库名.git
   git push -u origin main
   ```
3. **查看构建进度**：访问 https://github.com/你的用户名/仓库名/actions
4. **下载结果**：构建完成后下载Windows构建产物

---

## 💻 如果您有Windows电脑

### 直接在Windows上构建：
1. **下载项目代码到Windows电脑**
2. **安装必要工具**：
   - Visual Studio Community 2019+ (免费)
   - Qt 5.15.2 官方安装器
   - CMake (cmake.org)
3. **运行构建**：
   ```cmd
   # 双击运行或命令行执行
   build_windows.bat
   ```
4. **获得安装包**：`五子棋游戏-1.0.0-Windows.exe`

---

## ⚡ 立即开始

### 选择最适合您的方案：
- ✅ **有GitHub账号** → 使用方案1（自动构建）
- ✅ **有Windows电脑** → 使用方案2（本地构建）
- ✅ **想要最简单** → 使用GitHub Actions

### 现在就开始：
```bash
# 一键触发GitHub构建
./trigger_windows_build.sh
```

---

## 📞 需要帮助？

查看详细指南：
- `Windows构建指南.md` - 完整的构建说明
- `故障排除指南.md` - 常见问题解决方案

