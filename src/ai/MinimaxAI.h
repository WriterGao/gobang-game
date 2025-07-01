#ifndef MINIMAXAI_H
#define MINIMAXAI_H

#include "AIPlayer.h"
#include "core/GameRule.h"
#include <QHash>
#include <climits>

// 为QPoint提供hash函数
inline uint qHash(const QPoint &key, uint seed = 0) {
    return qHash(key.x(), seed) ^ qHash(key.y(), seed);
}

class MinimaxAI : public AIPlayer
{
    Q_OBJECT

public:
    explicit MinimaxAI(ChessBoard::PieceType pieceType, int difficulty = 2, QObject *parent = nullptr);

protected:
    QPoint calculateMove(const ChessBoard* board) override;

private:
    struct MoveScore {
        QPoint position;
        int score;
        
        MoveScore(const QPoint& pos = QPoint(-1, -1), int s = 0) : position(pos), score(s) {}
    };
    
    MoveScore minimax(ChessBoard* board, int depth, bool isMaximizing, 
                     int alpha = INT_MIN, int beta = INT_MAX);
    
    int evaluateBoard(const ChessBoard* board) const;
    int evaluatePosition(const QPoint& position, ChessBoard::PieceType type, const ChessBoard* board) const;
    int evaluateLine(const QPoint& position, const QPoint& direction, 
                    ChessBoard::PieceType type, const ChessBoard* board) const;
    
    QList<QPoint> generateCandidateMoves(const ChessBoard* board) const;
    QList<QPoint> getNeighborPositions(const QPoint& position, int radius = 2) const;
    
    bool isImportantPosition(const QPoint& position, const ChessBoard* board) const;
    int getMaxDepth() const;
    
    GameRule* m_rule;
    
    // 评估权重
    static const int WIN_SCORE = 1000000;
    static const int BLOCK_WIN_SCORE = 100000;
    static const int FOUR_SCORE = 10000;
    static const int BLOCK_FOUR_SCORE = 1000;
    static const int THREE_SCORE = 1000;
    static const int BLOCK_THREE_SCORE = 100;
    static const int TWO_SCORE = 100;
    static const int ONE_SCORE = 10;
};

#endif // MINIMAXAI_H 