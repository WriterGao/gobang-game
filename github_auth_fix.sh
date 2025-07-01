#!/bin/bash

echo "🔐 GitHub认证问题解决助手"
echo "========================="
echo ""

echo "📋 快速解决方案："
echo ""
echo "1️⃣ 首先，在浏览器中打开："
echo "   https://github.com/settings/tokens"
echo ""
echo "2️⃣ 创建新token："
echo "   • 点击 'Generate new token (classic)'"
echo "   • 描述：Gobang Game Project"
echo "   • 权限勾选：repo + workflow"
echo "   • 点击 'Generate token'"
echo "   • 复制生成的token（ghp_开头的长字符串）"
echo ""
echo "3️⃣ 使用token推送代码："
echo "   $ git push -f origin main"
echo "   Username: WriterGao"
echo "   Password: [粘贴您的token]"
echo ""

echo "💡 更方便的解决方案："
echo ""
echo "如果您有token，可以运行："
echo "   $ git remote set-url origin https://WriterGao:[YOUR_TOKEN]@github.com/WriterGao/gobang-game.git"
echo "然后直接："
echo "   $ git push -f origin main"
echo ""

echo "🔗 有用的链接："
echo "   • Token设置：https://github.com/settings/tokens"
echo "   • GitHub文档：https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/creating-a-personal-access-token"
echo ""

read -p "📝 您是否已经创建了Personal Access Token？ (y/n): " has_token

if [[ $has_token == "y" || $has_token == "Y" ]]; then
    echo ""
    read -p "🔑 请输入您的token: " token
    if [[ ! -z "$token" ]]; then
        echo ""
        echo "⚙️ 正在设置远程URL..."
        git remote set-url origin "https://WriterGao:$token@github.com/WriterGao/gobang-game.git"
        echo "✅ 远程URL已更新"
        echo ""
        echo "🚀 现在尝试推送..."
        git push -f origin main
    else
        echo "❌ Token不能为空"
    fi
else
    echo ""
    echo "📱 请先按照上面的步骤创建token，然后重新运行此脚本"
fi 