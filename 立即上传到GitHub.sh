#!/bin/bash

echo "🚀 五子棋项目 - 立即上传到GitHub"
echo "================================="

# 检查是否已配置Git用户信息
if ! git config user.name >/dev/null 2>&1; then
    echo "⚠️ 需要先配置Git用户信息"
    echo "请执行以下命令："
    echo "git config --global user.name \"您的姓名\""
    echo "git config --global user.email \"您的邮箱\""
    echo ""
    read -p "是否现在配置？(y/n): " config_git
    if [ "$config_git" = "y" ]; then
        read -p "请输入您的姓名: " git_name
        read -p "请输入您的邮箱: " git_email
        git config --global user.name "$git_name"
        git config --global user.email "$git_email"
        echo "✅ Git用户信息配置完成"
    else
        echo "请先配置Git用户信息后再运行此脚本"
        exit 1
    fi
fi

echo ""
echo "📝 请输入您在GitHub上创建的仓库信息："
echo "格式示例: https://github.com/zhangsan/gobang-game.git"
echo ""
read -p "请输入完整的仓库URL: " repo_url

if [ -z "$repo_url" ]; then
    echo "❌ 仓库URL不能为空"
    exit 1
fi

echo ""
echo "🔧 开始上传项目..."

# 1. 初始化Git仓库
echo "1️⃣ 初始化Git仓库..."
git init

# 2. 添加所有文件
echo "2️⃣ 添加项目文件..."
git add .

# 3. 创建第一次提交
echo "3️⃣ 创建提交..."
git commit -m "五子棋游戏完整项目

✨ 功能特色：
- 跨平台支持 (Windows/macOS/Linux)
- 智能AI对战 (3个难度等级)
- 完整多媒体系统 (背景音乐+音效+背景图片)
- 现代化Qt GUI界面
- 完善的设置系统
- 自动化构建和打包

🏗️ 技术栈：
- C++17 + Qt 5.15
- CMake构建系统
- GitHub Actions CI/CD
- 跨平台音频处理

📦 构建支持：
- macOS: ./build_macos.sh
- Windows: build_windows.bat  
- Linux: ./build_linux.sh
- 自动化: GitHub Actions"

# 4. 设置主分支
echo "4️⃣ 设置主分支..."
git branch -M main

# 5. 添加远程仓库
echo "5️⃣ 连接GitHub仓库..."
git remote add origin "$repo_url"

# 6. 推送到GitHub
echo "6️⃣ 推送到GitHub..."
echo "正在上传文件，请稍候..."
git push -u origin main

if [ $? -eq 0 ]; then
    echo ""
    echo "🎉 上传成功！"
    echo "========================"
    echo ""
    echo "📍 您的项目地址："
    echo "   ${repo_url%.git}"
    echo ""
    echo "🔄 GitHub Actions构建状态："
    echo "   ${repo_url%.git}/actions"
    echo ""
    echo "⏱️ 构建时间：约10-15分钟"
    echo ""
    echo "📦 构建完成后下载方法："
    echo "1. 访问Actions页面"
    echo "2. 点击最新的workflow运行"
    echo "3. 滚动到底部查看Artifacts"
    echo "4. 下载'五子棋游戏-Windows'"
    echo "5. 解压得到Windows安装包(.exe)"
    echo ""
    echo "🎯 现在可以在浏览器中查看构建进度！"
else
    echo "❌ 上传失败"
    echo "请检查："
    echo "1. 网络连接"
    echo "2. GitHub仓库URL是否正确"
    echo "3. 是否有仓库权限"
fi

