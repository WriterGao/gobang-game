#!/bin/bash

echo "🚀 快速开始Windows构建"
echo "===================="

echo "选择构建方案："
echo "1) GitHub Actions自动构建（推荐）"
echo "2) 查看Windows构建脚本"
echo "3) 显示详细指南"
echo ""

read -p "请选择 (1-3): " choice

case $choice in
    1)
        echo "🔧 设置GitHub自动构建..."
        echo ""
        echo "步骤1: 创建GitHub仓库"
        echo "  - 访问 https://github.com/new"
        echo "  - 仓库名: gobang-game 或您喜欢的名字"
        echo "  - 设为公开仓库（使用免费Actions）"
        echo ""
        echo "步骤2: 上传项目代码"
        echo "执行以下命令："
        echo ""
        echo "git init"
        echo "git add ."
        echo "git commit -m '五子棋游戏完整项目'"
        echo "git branch -M main"
        echo "git remote add origin https://github.com/YOUR_USERNAME/YOUR_REPO.git"
        echo "git push -u origin main"
        echo ""
        echo "步骤3: 查看构建进度"
        echo "  - 访问 https://github.com/YOUR_USERNAME/YOUR_REPO/actions"
        echo "  - 等待约10-15分钟"
        echo "  - 下载 'Windows构建产物'"
        echo ""
        echo "🎯 替换YOUR_USERNAME和YOUR_REPO为您的实际GitHub信息"
        ;;
    2)
        echo "📄 Windows构建脚本内容："
        echo "========================"
        head -20 build_windows.bat
        echo ""
        echo "💡 这个脚本需要在Windows系统上运行"
        echo "📁 完整脚本: build_windows.bat"
        ;;
    3)
        echo "📚 详细指南文件："
        echo "=================="
        echo "- Windows构建指南.md"
        echo "- 立即构建Windows版本.md" 
        echo "- 故障排除指南.md"
        echo ""
        echo "📖 建议先阅读：立即构建Windows版本.md"
        ;;
    *)
        echo "❌ 无效选择"
        ;;
esac
