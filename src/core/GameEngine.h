#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QElapsedTimer>
#include "ChessBoard.h"
#include "GameRule.h"
#include "Player.h"

class GameEngine : public QObject
{
    Q_OBJECT

public:
    enum GameMode { PvP = 0, PvC = 1, Network = 2 };
    enum GameState { Ready = 0, Playing = 1, Paused = 2, Finished = 3 };
    
    explicit GameEngine(QObject *parent = nullptr);
    ~GameEngine();
    
    // 游戏控制
    void startNewGame(GameMode mode = PvP);
    void pauseGame();
    void resumeGame();
    void endGame();
    void restartGame();
    
    // 下棋操作
    bool makeMove(const QPoint& position);
    bool undoMove();
    bool canUndo() const;
    
    // 状态查询
    GameState gameState() const { return m_state; }
    GameMode gameMode() const { return m_mode; }
    ChessBoard::PieceType currentPlayer() const;
    ChessBoard::PieceType winner() const { return m_winner; }
    bool isGameFinished() const { return m_state == Finished; }
    int moveCount() const;
    int undoCount() const { return m_undoCount; }
    qint64 elapsedTime() const;
    
    // 获取游戏组件
    ChessBoard* chessBoard() const { return m_board; }
    GameRule* gameRule() const { return m_rule; }
    Player* player(int index) const;
    Player* currentPlayerObject() const;
    
    // 配置管理
    void setGameMode(GameMode mode);
    void setAIDifficulty(int difficulty);

signals:
    void gameStateChanged(GameState newState);
    void playerChanged(ChessBoard::PieceType player);
    void moveMade(const QPoint& position, ChessBoard::PieceType piece);
    void moveUndone(const QPoint& position);
    void gameWon(ChessBoard::PieceType winner);
    void gameDraw();
    void errorOccurred(const QString& message);

private slots:
    void onPlayerMoveReady(const QPoint& position);
    void onPlayerMoveCancelled();

private:
    void initializeGame();
    void setupPlayers();
    void switchPlayer();
    void checkGameEnd();
    void notifyGameEnd();
    void requestPlayerMove();
    
    ChessBoard* m_board;
    GameRule* m_rule;
    Player* m_players[2];
    GameState m_state;
    GameMode m_mode;
    int m_currentPlayerIndex;
    ChessBoard::PieceType m_winner;
    QElapsedTimer m_gameTimer;
    int m_undoCount;
    int m_aiDifficulty;
};

#endif // GAMEENGINE_H 