#ifndef AIPLAYER_H
#define AIPLAYER_H

#include <QThread>
#include <QFutureWatcher>
#include "core/Player.h"

// AI玩家基类
class AIPlayer : public Player
{
    Q_OBJECT

public:
    explicit AIPlayer(ChessBoard::PieceType pieceType, int difficulty = 2, QObject *parent = nullptr);
    ~AIPlayer();
    
    PlayerType type() const override { return AI; }
    void requestMove(const ChessBoard* board) override;
    void cancelMove() override;
    bool isThinking() const override { return m_thinking; }
    
    int difficulty() const { return m_difficulty; }
    void setDifficulty(int difficulty) { m_difficulty = difficulty; }

protected:
    virtual QPoint calculateMove(const ChessBoard* board) = 0;

private slots:
    void onCalculationFinished();

private:
    QFutureWatcher<QPoint>* m_watcher;
    bool m_thinking;
    int m_difficulty;
};

#endif // AIPLAYER_H 