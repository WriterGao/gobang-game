#!/bin/bash

echo "🚀 GitHub上传指南"
echo "=================="

echo "请在创建GitHub仓库后，将下面的USERNAME和REPO_NAME替换为您的实际信息："
echo ""

echo "您的GitHub用户名: YOUR_USERNAME"
echo "仓库名: YOUR_REPO_NAME"
echo ""

echo "然后按顺序执行以下命令："
echo ""

echo "# 1. 初始化Git仓库（如果还没有）"
echo "git init"
echo ""

echo "# 2. 添加所有文件"
echo "git add ."
echo ""

echo "# 3. 创建第一次提交"
echo "git commit -m \"五子棋游戏完整项目 - 支持跨平台构建\""
echo ""

echo "# 4. 设置主分支名"
echo "git branch -M main"
echo ""

echo "# 5. 添加远程仓库（替换YOUR_USERNAME和YOUR_REPO_NAME）"
echo "git remote add origin https://github.com/YOUR_USERNAME/YOUR_REPO_NAME.git"
echo ""

echo "# 6. 推送到GitHub"
echo "git push -u origin main"
echo ""

echo "📋 示例（请替换为您的信息）："
echo "git remote add origin https://github.com/zhangsan/gobang-game.git"

