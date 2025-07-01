#!/bin/bash

# GitHub Actions Windows构建触发脚本

echo "🚀 触发Windows版本构建"
echo "========================="

# 检查Git状态
if ! git status &>/dev/null; then
    echo "❌ 错误：当前目录不是Git仓库"
    echo "请先初始化Git仓库："
    echo "  git init"
    echo "  git remote add origin <your-repo-url>"
    exit 1
fi

# 检查是否有远程仓库
if ! git remote get-url origin &>/dev/null; then
    echo "❌ 错误：未配置GitHub远程仓库"
    echo "请先添加远程仓库："
    echo "  git remote add origin https://github.com/username/repository.git"
    exit 1
fi

echo "📝 准备构建提交..."

# 添加所有文件
git add .

# 创建构建提交
COMMIT_MSG="触发Windows构建 - $(date '+%Y-%m-%d %H:%M:%S')"
git commit -m "$COMMIT_MSG"

if [ $? -eq 0 ]; then
    echo "✅ 提交创建成功"
else
    echo "ℹ️ 没有新的更改需要提交"
fi

echo "🚀 推送到GitHub..."
git push origin main

if [ $? -eq 0 ]; then
    echo "✅ 推送成功！"
    echo ""
    echo "🔗 查看构建进度："
    REPO_URL=$(git remote get-url origin)
    REPO_URL=${REPO_URL%.git}
    echo "   ${REPO_URL}/actions"
    echo ""
    echo "⏱️ 预计构建时间：10-15分钟"
    echo "📦 构建完成后，在Actions页面下载Windows安装包"
    echo ""
    echo "🎯 下载步骤："
    echo "1. 访问上述链接"
    echo "2. 点击最新的workflow运行"
    echo "3. 滚动到底部的'Artifacts'部分"
    echo "4. 下载'五子棋游戏-Windows'"
    echo "5. 解压得到.exe安装包"
else
    echo "❌ 推送失败"
    echo "请检查GitHub仓库配置和网络连接"
    exit 1
fi
