#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

#include "GameWidget.h"
#include "core/GameEngine.h"
#include "managers/ConfigManager.h"
#include "managers/AudioManager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    // 菜单操作
    void onNewGame();
    void onNewPvPGame();
    void onNewPvCGame();
    void onPauseGame();
    void onRestartGame();
    void onUndo();
    void onSettings();
    void onExit();
    void onAbout();
    
    // 游戏状态响应
    void onGameStateChanged(GameEngine::GameState state);
    void onPlayerChanged(ChessBoard::PieceType player);
    void onMoveMade(const QPoint& position, ChessBoard::PieceType piece);
    void onGameWon(ChessBoard::PieceType winner);
    void onGameDraw();
    void onErrorOccurred(const QString& message);
    
    // UI更新
    void updateUI();
    void updateStatusBar();
    
    // 辅助函数
    QString formatTime(qint64 milliseconds) const;

private:
    void setupUI();
    void setupMenuBar();
    void setupToolBar();
    void setupStatusBar();
    void setupCentralWidget();
    void connectSignals();
    
    // UI组件
    GameWidget* m_gameWidget;
    QWidget* m_infoPanel;
    
    // 信息显示
    QLabel* m_currentPlayerLabel;
    QLabel* m_gameTimeLabel;
    QLabel* m_moveCountLabel;
    QLabel* m_undoCountLabel;
    QLabel* m_gameStateLabel;
    
    // 操作按钮
    QPushButton* m_newGameButton;
    QPushButton* m_undoButton;
    QPushButton* m_pauseButton;
    QPushButton* m_restartButton;
    
    // 计时器
    QTimer* m_uiUpdateTimer;
    
    // 核心组件
    GameEngine* m_gameEngine;
    ConfigManager* m_configManager;
    AudioManager* m_audioManager;
};

#endif // MAINWINDOW_H 