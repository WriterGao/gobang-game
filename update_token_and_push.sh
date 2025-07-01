#!/bin/bash

echo "🔄 更新Token并启用Windows自动构建"
echo "================================="
echo ""

echo "📝 请确保您已经创建了包含以下权限的新token："
echo "   ✅ repo (仓库权限)"
echo "   ✅ workflow (GitHub Actions权限)"
echo ""

read -p "🔑 请输入您的新token: " new_token

if [[ -z "$new_token" ]]; then
    echo "❌ Token不能为空！"
    exit 1
fi

echo ""
echo "⚙️ 正在更新Git远程URL..."
git remote set-url origin "https://WriterGao:$new_token@github.com/WriterGao/gobang-game.git"

echo "✅ Git远程URL已更新"
echo ""

echo "🚀 正在推送GitHub Actions配置..."
if git push origin main; then
    echo ""
    echo "🎉 成功！GitHub Actions配置已推送"
    echo "📱 访问以下链接查看构建进度："
    echo "   https://github.com/WriterGao/gobang-game/actions"
    echo ""
    echo "⏱️ Windows构建大约需要10-15分钟"
    echo "📦 构建完成后，您可以在Actions页面下载Windows安装包"
    echo ""
    echo "🔗 直接下载链接（构建完成后）："
    echo "   https://github.com/WriterGao/gobang-game/actions"
else
    echo ""
    echo "❌ 推送失败，请检查："
    echo "1. Token是否正确"
    echo "2. Token是否包含workflow权限"
    echo "3. 网络连接是否正常"
fi 