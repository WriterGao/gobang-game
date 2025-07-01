#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QString>
#include <QPoint>
#include "ChessBoard.h"

class Player : public QObject
{
    Q_OBJECT

public:
    enum PlayerType { Human = 0, AI = 1 };
    
    explicit Player(ChessBoard::PieceType pieceType, QObject *parent = nullptr);
    virtual ~Player() = default;
    
    // 基本属性
    virtual PlayerType type() const = 0;
    ChessBoard::PieceType pieceType() const { return m_pieceType; }
    QString name() const { return m_name; }
    void setName(const QString& name) { m_name = name; }
    
    // 游戏操作
    virtual void requestMove(const ChessBoard* board) = 0;
    virtual void cancelMove() {}
    virtual bool isThinking() const { return false; }

signals:
    void moveReady(const QPoint& position);
    void moveCancelled();

protected:
    ChessBoard::PieceType m_pieceType;
    QString m_name;
};

// 人类玩家实现
class HumanPlayer : public Player
{
    Q_OBJECT

public:
    explicit HumanPlayer(ChessBoard::PieceType pieceType, QObject *parent = nullptr);
    
    PlayerType type() const override { return Human; }
    void requestMove(const ChessBoard* board) override;
    void makeMove(const QPoint& position);

private:
    bool m_waitingForMove;
};

#endif // PLAYER_H 