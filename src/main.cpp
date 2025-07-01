#include <QApplication>
#include <QStyleFactory>
#include <QDir>
#include <QStandardPaths>
#include <QDebug>

#include "ui/MainWindow.h"
#include "managers/ConfigManager.h"
#include "managers/AudioManager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // 设置应用程序信息
    app.setApplicationName("Gobang");
    app.setApplicationDisplayName("五子棋游戏");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("GobangGame");
    app.setOrganizationDomain("gobang.game");
    
    // 设置应用程序图标
    // app.setWindowIcon(QIcon(":/icons/gobang.png"));
    
    // 初始化配置管理器
    ConfigManager* configManager = ConfigManager::instance();
    AudioManager* audioManager = AudioManager::instance();
    
    // 设置应用程序退出时的清理
    QObject::connect(&app, &QApplication::aboutToQuit, [audioManager]() {
        qDebug() << "应用程序即将退出，停止背景音乐...";
        audioManager->stopBackgroundMusic();
        // 确保清理所有afplay进程
        #if defined(Q_OS_MAC)
        system("killall afplay 2>/dev/null");
        #endif
    });
    
    // 设置应用程序样式
    app.setStyle(QStyleFactory::create("Fusion"));
    
    // 创建主窗口
    MainWindow window;
    window.show();
    
    qDebug() << "五子棋游戏启动成功";
    qDebug() << "配置文件路径:" << QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
    
    int result = app.exec();
    
    // 额外的清理确保
    qDebug() << "应用程序退出，执行最终清理...";
    audioManager->stopBackgroundMusic();
    #if defined(Q_OS_MAC)
    system("killall afplay 2>/dev/null");
    #endif
    
    return result;
} 