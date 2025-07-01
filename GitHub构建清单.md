# 🚀 GitHub Actions Windows构建 - 操作清单

## ✅ 准备工作
- [ ] 有GitHub账号
- [ ] 项目文件完整（已完成）
- [ ] 网络连接正常

## 📝 步骤1：创建GitHub仓库
- [ ] 打开 https://github.com/new
- [ ] 输入仓库名：gobang-game
- [ ] 选择Public（免费Actions）
- [ ] 不勾选任何初始化选项
- [ ] 点击"Create repository"
- [ ] 复制仓库URL（例如：https://github.com/用户名/gobang-game.git）

## 🔄 步骤2：上传项目
选择一种方式：

### 方式A：自动上传（推荐）
- [ ] 运行：`./立即上传到GitHub.sh`
- [ ] 按提示输入仓库URL
- [ ] 等待上传完成

### 方式B：手动上传
- [ ] `git init`
- [ ] `git config --global user.name "您的姓名"`
- [ ] `git config --global user.email "您的邮箱"`
- [ ] `git add .`
- [ ] `git commit -m "五子棋游戏完整项目"`
- [ ] `git branch -M main`
- [ ] `git remote add origin 您的仓库URL`
- [ ] `git push -u origin main`

## 🏗️ 步骤3：查看构建进度
- [ ] 访问：https://github.com/您的用户名/仓库名/actions
- [ ] 等待构建完成（10-15分钟）
- [ ] 构建状态显示绿色✅

## 📦 步骤4：下载Windows安装包
- [ ] 点击最新的构建任务
- [ ] 滚动到页面底部
- [ ] 找到"Artifacts"部分
- [ ] 下载"五子棋游戏-Windows"
- [ ] 解压得到.exe安装包

## 🎉 完成！
- [ ] Windows安装包：五子棋游戏-1.0.0-Windows.exe
- [ ] macOS安装包：五子棋游戏-1.0.0-macOS.dmg（已有）

---

💡 **提示**：如有问题，请查看`故障排除指南.md`
