# 五子棋游戏 Qt库文件快速获取脚本
Write-Host "=====================================" -ForegroundColor Cyan
Write-Host "    五子棋游戏 Qt库文件快速获取工具    " -ForegroundColor Cyan  
Write-Host "=====================================" -ForegroundColor Cyan
Write-Host ""

# 检查是否在正确的目录
if (-not (Test-Path "bin\Gobang.exe")) {
    Write-Host "❌ 错误：请将此脚本放在包含bin目录的游戏文件夹中！" -ForegroundColor Red
    Write-Host "当前目录应该包含：bin\Gobang.exe" -ForegroundColor Yellow
    Read-Host "按回车键退出"
    exit 1
}

Write-Host "✅ 找到游戏可执行文件：bin\Gobang.exe" -ForegroundColor Green
Write-Host ""

# 检查缺失的文件
$requiredFiles = @(
    "bin\Qt5Core.dll",
    "bin\Qt5Gui.dll", 
    "bin\Qt5Widgets.dll",
    "bin\Qt5Multimedia.dll"
)

$missingFiles = @()
foreach ($file in $requiredFiles) {
    if (-not (Test-Path $file)) {
        $filename = Split-Path $file -Leaf
        Write-Host "[缺失] $filename" -ForegroundColor Red
        $missingFiles += $filename
    } else {
        $filename = Split-Path $file -Leaf
        Write-Host "[存在] $filename" -ForegroundColor Green
    }
}

if ($missingFiles.Count -eq 0) {
    Write-Host ""
    Write-Host "🎉 所有Qt库文件都已存在！您可以直接运行游戏了！" -ForegroundColor Green
    $runGame = Read-Host "是否现在运行游戏？(y/n)"
    if ($runGame -eq "y" -or $runGame -eq "Y") {
        Start-Process "bin\Gobang.exe"
    }
    exit 0
}

Write-Host ""
Write-Host "需要获取 $($missingFiles.Count) 个Qt库文件" -ForegroundColor Yellow
Write-Host ""

# 搜索本地Qt安装
Write-Host "🔍 正在搜索本地Qt安装..." -ForegroundColor Cyan

$qtPaths = @(
    "C:\Qt\5.15.2\msvc2019_64",
    "C:\Qt\Qt5.15.2\5.15.2\msvc2019_64",
    "D:\Qt\5.15.2\msvc2019_64",
    "E:\Qt\5.15.2\msvc2019_64"
)

$foundQt = $null
foreach ($path in $qtPaths) {
    if (Test-Path "$path\bin\Qt5Core.dll") {
        Write-Host "✅ 找到Qt安装：$path" -ForegroundColor Green
        $foundQt = $path
        break
    }
}

if ($foundQt) {
    Write-Host ""
    $copyChoice = Read-Host "是否从本地Qt安装复制库文件？(y/n)"
    
    if ($copyChoice -eq "y" -or $copyChoice -eq "Y") {
        Write-Host ""
        Write-Host "📋 正在复制Qt库文件..." -ForegroundColor Cyan
        
        foreach ($file in $missingFiles) {
            $sourcePath = "$foundQt\bin\$file"
            $destPath = "bin\$file"
            
            if (Test-Path $sourcePath) {
                try {
                    Copy-Item $sourcePath $destPath -Force
                    Write-Host "✅ 复制 $file 成功" -ForegroundColor Green
                } catch {
                    Write-Host "❌ 复制 $file 失败：$_" -ForegroundColor Red
                }
            } else {
                Write-Host "⚠️ 在Qt安装中未找到 $file" -ForegroundColor Yellow
            }
        }
        
        # 复制平台插件
        $platformsSource = "$foundQt\plugins\platforms\qwindows.dll"
        if (Test-Path $platformsSource) {
            if (-not (Test-Path "bin\platforms")) {
                New-Item -ItemType Directory -Path "bin\platforms" -Force | Out-Null
            }
            try {
                Copy-Item $platformsSource "bin\platforms\" -Force
                Write-Host "✅ 复制 qwindows.dll 平台插件成功" -ForegroundColor Green
            } catch {
                Write-Host "❌ 复制平台插件失败：$_" -ForegroundColor Red
            }
        }
        
        Write-Host ""
        Write-Host "🎯 复制完成！" -ForegroundColor Green
        $runGame = Read-Host "是否现在运行游戏？(y/n)"
        if ($runGame -eq "y" -or $runGame -eq "Y") {
            Start-Process "bin\Gobang.exe"
        }
        exit 0
    }
}

# 提供其他获取方式
Write-Host ""
Write-Host "📥 其他获取Qt库文件的方式：" -ForegroundColor Cyan
Write-Host ""
Write-Host "1. 在线下载DLL文件" -ForegroundColor White
Write-Host "2. 安装Qt官方版本" -ForegroundColor White
Write-Host "3. 显示手动操作指南" -ForegroundColor White
Write-Host "4. 退出" -ForegroundColor White
Write-Host ""

$choice = Read-Host "请选择 (1-4)"

switch ($choice) {
    "1" {
        Write-Host ""
        Write-Host "🌐 正在打开DLL下载页面..." -ForegroundColor Cyan
        Write-Host "请下载以下文件的64位版本：" -ForegroundColor Yellow
        
        $dllUrls = @{
            "Qt5Core.dll" = "https://www.dll-files.com/qt5core.dll.html"
            "Qt5Gui.dll" = "https://www.dll-files.com/qt5gui.dll.html"
            "Qt5Widgets.dll" = "https://www.dll-files.com/qt5widgets.dll.html"
            "Qt5Multimedia.dll" = "https://www.dll-files.com/qt5multimedia.dll.html"
        }
        
        foreach ($dll in $missingFiles) {
            if ($dllUrls.ContainsKey($dll)) {
                Write-Host "正在打开 $dll 下载页面..." -ForegroundColor Green
                Start-Process $dllUrls[$dll]
                Start-Sleep -Seconds 2
            }
        }
        
        Write-Host ""
        Write-Host "💡 下载提示：" -ForegroundColor Yellow
        Write-Host "• 选择64位(x64)版本" -ForegroundColor White
        Write-Host "• 下载后将DLL文件复制到bin目录" -ForegroundColor White
        Write-Host "• 完成后重新运行此脚本检查" -ForegroundColor White
    }
    
    "2" {
        Write-Host ""
        Write-Host "🌐 正在打开Qt官方下载页面..." -ForegroundColor Cyan
        Start-Process "https://www.qt.io/download-open-source"
        Write-Host ""
        Write-Host "📝 安装指南：" -ForegroundColor Yellow
        Write-Host "• 选择开源版本下载" -ForegroundColor White
        Write-Host "• 安装时选择 Qt 5.15.2" -ForegroundColor White
        Write-Host "• 选择 MSVC 2019 64-bit 组件" -ForegroundColor White
        Write-Host "• 安装后重新运行此脚本" -ForegroundColor White
    }
    
    "3" {
        Write-Host ""
        Write-Host "📋 手动操作指南：" -ForegroundColor Cyan
        Write-Host "================" -ForegroundColor Cyan
        Write-Host ""
        Write-Host "需要的文件：" -ForegroundColor Yellow
        foreach ($file in $missingFiles) {
            Write-Host "  • $file" -ForegroundColor White
        }
        Write-Host ""
        Write-Host "获取方式：" -ForegroundColor Yellow
        Write-Host "1. 从Qt安装目录复制（推荐）：" -ForegroundColor White
        Write-Host "   C:\Qt\5.15.2\msvc2019_64\bin\" -ForegroundColor Gray
        Write-Host ""
        Write-Host "2. 在线下载：" -ForegroundColor White
        Write-Host "   访问 dll-files.com 搜索各个DLL" -ForegroundColor Gray
        Write-Host ""
        Write-Host "3. 安装完整Qt：" -ForegroundColor White
        Write-Host "   访问 qt.io 下载并安装" -ForegroundColor Gray
        Write-Host ""
        Write-Host "部署位置：" -ForegroundColor Yellow
        Write-Host "  将DLL文件复制到 bin\ 目录" -ForegroundColor White
    }
    
    default {
        Write-Host "再见！" -ForegroundColor Green
        exit 0
    }
}

Write-Host ""
Read-Host "按回车键退出" 