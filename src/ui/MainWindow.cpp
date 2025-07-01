#include "MainWindow.h"
#include "ui/SettingsDialog.h"
#include <QApplication>
#include <QCloseEvent>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_gameWidget(nullptr)
    , m_infoPanel(nullptr)
    , m_uiUpdateTimer(new QTimer(this))
    , m_gameEngine(new GameEngine(this))
    , m_configManager(ConfigManager::instance())
    , m_audioManager(AudioManager::instance())
{
    setupUI();
    connectSignals();
    
    // 启动UI更新计时器
    m_uiUpdateTimer->start(1000); // 每秒更新一次
    
    // 如果配置了背景音乐，则启动播放
    if (!m_configManager->backgroundMusic().isEmpty()) {
        m_audioManager->playBackgroundMusic();
    }
    
    // 设置窗口属性
    setWindowTitle("五子棋游戏");
    resize(m_configManager->windowSize());
}

MainWindow::~MainWindow()
{
    // 停止背景音乐
    m_audioManager->stopBackgroundMusic();
    
    m_configManager->setWindowSize(size());
    m_configManager->saveSettings();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // 停止背景音乐
    m_audioManager->stopBackgroundMusic();
    
    m_configManager->setWindowSize(size());
    m_configManager->saveSettings();
    event->accept();
}

void MainWindow::setupUI()
{
    setupCentralWidget();
    setupMenuBar();
    setupToolBar();
    setupStatusBar();
}

void MainWindow::setupMenuBar()
{
    QMenuBar* menuBar = this->menuBar();
    
    // 游戏菜单
    QMenu* gameMenu = menuBar->addMenu("游戏(&G)");
    
    QAction* newPvPAction = gameMenu->addAction("人人对战(&P)");
    connect(newPvPAction, &QAction::triggered, this, &MainWindow::onNewPvPGame);
    
    QAction* newPvCAction = gameMenu->addAction("人机对战(&C)");
    connect(newPvCAction, &QAction::triggered, this, &MainWindow::onNewPvCGame);
    
    gameMenu->addSeparator();
    
    QAction* pauseAction = gameMenu->addAction("暂停游戏(&S)");
    connect(pauseAction, &QAction::triggered, this, &MainWindow::onPauseGame);
    
    QAction* restartAction = gameMenu->addAction("重新开始(&R)");
    connect(restartAction, &QAction::triggered, this, &MainWindow::onRestartGame);
    
    gameMenu->addSeparator();
    
    QAction* settingsAction = gameMenu->addAction("设置(&T)");
    connect(settingsAction, &QAction::triggered, this, &MainWindow::onSettings);
    
    // 音频菜单
    QMenu* audioMenu = menuBar->addMenu("音频(&A)");
    
    QAction* toggleMusicAction = audioMenu->addAction("背景音乐开/关(&M)");
    connect(toggleMusicAction, &QAction::triggered, [this]() {
        static bool musicPlaying = true;
        if (musicPlaying) {
            m_audioManager->pauseBackgroundMusic();
        } else {
            m_audioManager->resumeBackgroundMusic();
        }
        musicPlaying = !musicPlaying;
    });
    
    gameMenu->addSeparator();
    
    QAction* exitAction = gameMenu->addAction("退出(&X)");
    connect(exitAction, &QAction::triggered, this, &MainWindow::onExit);
    
    // 帮助菜单
    QMenu* helpMenu = menuBar->addMenu("帮助(&H)");
    QAction* aboutAction = helpMenu->addAction("关于(&A)");
    connect(aboutAction, &QAction::triggered, this, &MainWindow::onAbout);
}

void MainWindow::setupToolBar()
{
    QToolBar* toolBar = addToolBar("主工具栏");
    
    QAction* newGameAction = toolBar->addAction("新游戏");
    connect(newGameAction, &QAction::triggered, this, &MainWindow::onNewGame);
    
    QAction* undoAction = toolBar->addAction("悔棋");
    connect(undoAction, &QAction::triggered, this, &MainWindow::onUndo);
    
    QAction* pauseAction = toolBar->addAction("暂停");
    connect(pauseAction, &QAction::triggered, this, &MainWindow::onPauseGame);
}

void MainWindow::setupStatusBar()
{
    QStatusBar* statusBar = this->statusBar();
    statusBar->showMessage("欢迎使用五子棋游戏");
}

void MainWindow::setupCentralWidget()
{
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
    
    // 创建游戏界面
    m_gameWidget = new GameWidget(this);
    m_gameWidget->setGameEngine(m_gameEngine);
    
    // 创建信息面板
    m_infoPanel = new QWidget(this);
    m_infoPanel->setFixedWidth(200);
    m_infoPanel->setStyleSheet("QWidget { background-color: #f0f0f0; border: 1px solid #ccc; }");
    
    QVBoxLayout* infoPanelLayout = new QVBoxLayout(m_infoPanel);
    
    // 游戏信息
    QLabel* gameInfoTitle = new QLabel("游戏信息", this);
    gameInfoTitle->setStyleSheet("font-weight: bold; font-size: 14px;");
    infoPanelLayout->addWidget(gameInfoTitle);
    
    m_gameStateLabel = new QLabel("准备开始", this);
    infoPanelLayout->addWidget(m_gameStateLabel);
    
    m_currentPlayerLabel = new QLabel("当前玩家: 黑方", this);
    infoPanelLayout->addWidget(m_currentPlayerLabel);
    
    m_gameTimeLabel = new QLabel("游戏时间: 00:00", this);
    infoPanelLayout->addWidget(m_gameTimeLabel);
    
    m_moveCountLabel = new QLabel("步数: 0", this);
    infoPanelLayout->addWidget(m_moveCountLabel);
    
    m_undoCountLabel = new QLabel("悔棋次数: 0", this);
    infoPanelLayout->addWidget(m_undoCountLabel);
    
    infoPanelLayout->addSpacing(20);
    
    // 操作按钮
    QLabel* operationTitle = new QLabel("游戏操作", this);
    operationTitle->setStyleSheet("font-weight: bold; font-size: 14px;");
    infoPanelLayout->addWidget(operationTitle);
    
    m_newGameButton = new QPushButton("新游戏", this);
    connect(m_newGameButton, &QPushButton::clicked, this, &MainWindow::onNewGame);
    infoPanelLayout->addWidget(m_newGameButton);
    
    m_undoButton = new QPushButton("悔棋", this);
    connect(m_undoButton, &QPushButton::clicked, this, &MainWindow::onUndo);
    infoPanelLayout->addWidget(m_undoButton);
    
    m_pauseButton = new QPushButton("暂停", this);
    connect(m_pauseButton, &QPushButton::clicked, this, &MainWindow::onPauseGame);
    infoPanelLayout->addWidget(m_pauseButton);
    
    m_restartButton = new QPushButton("重新开始", this);
    connect(m_restartButton, &QPushButton::clicked, this, &MainWindow::onRestartGame);
    infoPanelLayout->addWidget(m_restartButton);
    
    infoPanelLayout->addStretch();
    
    // 添加到主布局
    mainLayout->addWidget(m_gameWidget, 1);
    mainLayout->addWidget(m_infoPanel);
    
    updateUI();
}

void MainWindow::connectSignals()
{
    // 连接游戏引擎信号
    connect(m_gameEngine, &GameEngine::gameStateChanged,
            this, &MainWindow::onGameStateChanged);
    connect(m_gameEngine, &GameEngine::playerChanged,
            this, &MainWindow::onPlayerChanged);
    connect(m_gameEngine, &GameEngine::moveMade,
            this, &MainWindow::onMoveMade);
    connect(m_gameEngine, &GameEngine::gameWon,
            this, &MainWindow::onGameWon);
    connect(m_gameEngine, &GameEngine::gameDraw,
            this, &MainWindow::onGameDraw);
    connect(m_gameEngine, &GameEngine::errorOccurred,
            this, &MainWindow::onErrorOccurred);
    
    // 连接UI更新计时器
    connect(m_uiUpdateTimer, &QTimer::timeout,
            this, &MainWindow::updateUI);
}

void MainWindow::onNewGame()
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("选择游戏模式");
    msgBox.setText("请选择游戏模式：");
    
    QPushButton* pvpButton = msgBox.addButton("人人对战", QMessageBox::ActionRole);
    QPushButton* pvcButton = msgBox.addButton("人机对战", QMessageBox::ActionRole);
    msgBox.addButton("取消", QMessageBox::RejectRole);
    
    msgBox.exec();
    
    if (msgBox.clickedButton() == pvpButton) {
        onNewPvPGame();
    } else if (msgBox.clickedButton() == pvcButton) {
        onNewPvCGame();
    }
}

void MainWindow::onNewPvPGame()
{
    m_gameEngine->startNewGame(GameEngine::PvP);
    m_audioManager->playEffect(AudioManager::ButtonClick);
}

void MainWindow::onNewPvCGame()
{
    m_gameEngine->startNewGame(GameEngine::PvC);
    m_audioManager->playEffect(AudioManager::ButtonClick);
}

void MainWindow::onPauseGame()
{
    if (m_gameEngine->gameState() == GameEngine::Playing) {
        m_gameEngine->pauseGame();
        m_pauseButton->setText("继续");
    } else if (m_gameEngine->gameState() == GameEngine::Paused) {
        m_gameEngine->resumeGame();
        m_pauseButton->setText("暂停");
    }
    m_audioManager->playEffect(AudioManager::ButtonClick);
}

void MainWindow::onRestartGame()
{
    m_gameEngine->restartGame();
    m_audioManager->playEffect(AudioManager::ButtonClick);
}

void MainWindow::onUndo()
{
    if (m_gameEngine->undoMove()) {
        m_audioManager->playEffect(AudioManager::Undo);
    } else {
        m_audioManager->playEffect(AudioManager::Error);
    }
}

void MainWindow::onSettings()
{
    SettingsDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        // 应用设置更改
        m_gameWidget->setShowCoordinates(m_configManager->showCoordinates());
        m_audioManager->setMasterVolume(m_configManager->volume());
        m_audioManager->setMuted(!m_configManager->soundEffectsEnabled());
        
        // 更新背景音乐
        m_audioManager->stopBackgroundMusic();
        QString newMusicPath = m_configManager->backgroundMusic();
        if (!newMusicPath.isEmpty() && QFileInfo::exists(newMusicPath)) {
            m_audioManager->playBackgroundMusic();
            statusBar()->showMessage(QString("背景音乐已更新: %1").arg(QFileInfo(newMusicPath).baseName()), 3000);
        } else if (!newMusicPath.isEmpty()) {
            statusBar()->showMessage("背景音乐文件不存在", 3000);
        } else {
            statusBar()->showMessage("背景音乐已关闭", 3000);
        }
        
        // 更新游戏界面（包括背景图片）
        m_gameWidget->update();
        
        // 如果窗口大小发生变化，调整窗口
        QSize newSize = m_configManager->windowSize();
        if (newSize != size()) {
            resize(newSize);
        }
    }
    m_audioManager->playEffect(AudioManager::ButtonClick);
}

void MainWindow::onExit()
{
    // 确保停止背景音乐
    m_audioManager->stopBackgroundMusic();
    close();
}

void MainWindow::onAbout()
{
    QMessageBox::about(this, "关于五子棋游戏", 
                      "五子棋游戏 v1.0\n\n"
                      "这是一个基于Qt开发的五子棋游戏，支持人人对战和人机对战模式。\n\n"
                      "游戏规则：\n"
                      "- 黑方先手，白方后手\n"
                      "- 轮流在棋盘交叉点下棋\n"
                      "- 率先在横、竖、斜任一方向连成5子者获胜\n\n"
                      "操作说明：\n"
                      "- 鼠标点击棋盘下棋\n"
                      "- 可以悔棋和暂停游戏\n"
                      "- 支持人机对战，AI有多个难度级别");
}

void MainWindow::onGameStateChanged(GameEngine::GameState state)
{
    QString stateText;
    switch (state) {
        case GameEngine::Ready:
            stateText = "准备开始";
            break;
        case GameEngine::Playing:
            stateText = "游戏进行中";
            break;
        case GameEngine::Paused:
            stateText = "游戏已暂停";
            break;
        case GameEngine::Finished:
            stateText = "游戏结束";
            break;
    }
    m_gameStateLabel->setText(stateText);
    updateUI();
}

void MainWindow::onPlayerChanged(ChessBoard::PieceType player)
{
    QString playerText = (player == ChessBoard::Black) ? "黑方" : "白方";
    m_currentPlayerLabel->setText(QString("当前玩家: %1").arg(playerText));
}

void MainWindow::onMoveMade(const QPoint& position, ChessBoard::PieceType piece)
{
    Q_UNUSED(position)
    Q_UNUSED(piece)
    updateUI();
}

void MainWindow::onGameWon(ChessBoard::PieceType winner)
{
    QString winnerText = (winner == ChessBoard::Black) ? "黑方" : "白方";
    QMessageBox::information(this, "游戏结束", 
                           QString("恭喜！%1获胜！\n\n游戏用时: %2\n总步数: %3")
                           .arg(winnerText)
                           .arg(formatTime(m_gameEngine->elapsedTime()))
                           .arg(m_gameEngine->moveCount()));
    m_audioManager->playEffect(AudioManager::GameWon);
}

void MainWindow::onGameDraw()
{
    QMessageBox::information(this, "游戏结束", "平局！棋盘已满，无人获胜。");
    m_audioManager->playEffect(AudioManager::GameDraw);
}

void MainWindow::onErrorOccurred(const QString& message)
{
    statusBar()->showMessage(QString("错误: %1").arg(message), 3000);
    m_audioManager->playEffect(AudioManager::Error);
}

void MainWindow::updateUI()
{
    // 更新按钮状态
    bool gameActive = (m_gameEngine->gameState() == GameEngine::Playing || 
                      m_gameEngine->gameState() == GameEngine::Paused);
    
    m_undoButton->setEnabled(gameActive && m_gameEngine->canUndo());
    m_pauseButton->setEnabled(gameActive);
    m_restartButton->setEnabled(gameActive);
    
    // 更新暂停按钮文本
    if (m_gameEngine->gameState() == GameEngine::Paused) {
        m_pauseButton->setText("继续");
    } else {
        m_pauseButton->setText("暂停");
    }
    
    updateStatusBar();
}

void MainWindow::updateStatusBar()
{
    if (m_gameEngine->gameState() == GameEngine::Playing || 
        m_gameEngine->gameState() == GameEngine::Paused) {
        
        qint64 elapsed = m_gameEngine->elapsedTime();
        m_gameTimeLabel->setText(QString("游戏时间: %1").arg(formatTime(elapsed)));
        
        m_moveCountLabel->setText(QString("步数: %1").arg(m_gameEngine->moveCount()));
        m_undoCountLabel->setText(QString("悔棋次数: %1").arg(m_gameEngine->undoCount()));
    }
}

QString MainWindow::formatTime(qint64 milliseconds) const
{
    int seconds = milliseconds / 1000;
    int minutes = seconds / 60;
    seconds = seconds % 60;
    
    return QString("%1:%2").arg(minutes, 2, 10, QChar('0'))
                          .arg(seconds, 2, 10, QChar('0'));
} 