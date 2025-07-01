# 🔧 Windows版本手动修复指南

如果您下载的Windows版本提示"找不到Qt5xxx.dll"错误，请按照以下步骤手动修复：

## 📥 第一步：下载Qt运行时库

### 方案1：安装官方Qt运行时（推荐）
1. 访问Qt官网：https://www.qt.io/download
2. 下载并安装 "Qt Online Installer"
3. 在安装选项中选择：
   - Qt 5.15.2
   - MSVC 2019 64-bit
4. 安装后系统会自动配置Qt库路径

### 方案2：手动下载DLL文件
如果您不想安装完整的Qt，可以手动下载所需的DLL文件：

**必需的DLL文件列表：**
- `Qt5Core.dll`
- `Qt5Gui.dll`
- `Qt5Widgets.dll`
- `Qt5Multimedia.dll`
- `Qt5MultimediaWidgets.dll`
- `Qt5Concurrent.dll`

**下载来源：**
- 从已安装Qt的电脑复制（通常在 `C:\Qt\5.15.2\msvc2019_64\bin\`）
- 或从在线DLL库下载（如 dll-files.com）

## 🔧 第二步：部署DLL文件

1. **解压游戏安装包**
   - 将下载的 `Gobang-Game-Windows.zip` 解压到任意文件夹

2. **复制DLL文件**
   - 将上述6个DLL文件复制到游戏的 `bin` 目录中
   - 确保DLL文件与 `Gobang.exe` 在同一目录

3. **创建平台插件目录**
   - 在 `bin` 目录中创建 `platforms` 文件夹
   - 将 `qwindows.dll` 复制到 `platforms` 文件夹中
   - 完整路径：`bin/platforms/qwindows.dll`

## 📁 最终目录结构

```
五子棋游戏/
└── bin/
    ├── Gobang.exe          # 主程序
    ├── Qt5Core.dll         # Qt核心库
    ├── Qt5Gui.dll          # Qt图形库
    ├── Qt5Widgets.dll      # Qt界面库
    ├── Qt5Multimedia.dll   # Qt多媒体库
    ├── Qt5MultimediaWidgets.dll
    ├── Qt5Concurrent.dll   # Qt并发库
    └── platforms/
        └── qwindows.dll    # Windows平台插件
```

## 🎮 第三步：运行游戏

1. 双击 `Gobang.exe` 启动游戏
2. 如果仍有错误，检查：
   - 是否缺少Visual C++运行时（安装VC++ Redistributable）
   - DLL文件版本是否匹配（建议使用Qt 5.15.2版本）

## 🛠️ 常见问题解决

### Q: 提示"应用程序无法正常启动(0xc000007b)"
**A:** 这通常是64位/32位版本不匹配
- 确保下载的是64位版本的Qt库
- 或安装完整的Visual C++ Redistributable x64

### Q: 提示缺少其他DLL文件
**A:** 可能需要额外的依赖：
- `msvcp140.dll`
- `vcruntime140.dll`
- 安装最新的 Microsoft Visual C++ Redistributable

### Q: 游戏启动但没有音效
**A:** 音频功能正常，可能是：
- 系统音量设置
- 游戏内设置中关闭了音效
- Windows音频服务未启动

## 📞 获取帮助

如果按照以上步骤仍无法解决问题，请：
1. 记录具体的错误信息
2. 确认您的Windows版本（Windows 10/11 推荐）
3. 检查是否安装了最新的系统更新

**祝您游戏愉快！** 🎯 