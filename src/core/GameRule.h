#ifndef GAMERULE_H
#define GAMERULE_H

#include <QObject>
#include <QPoint>
#include <QList>
#include "ChessBoard.h"

class GameRule : public QObject
{
    Q_OBJECT

public:
    enum WinType { None = 0, Horizontal = 1, Vertical = 2, 
                   DiagonalMain = 3, DiagonalAnti = 4 };
    
    struct WinInfo {
        WinType type;
        QPoint startPos;
        QPoint endPos;
        ChessBoard::PieceType winner;
        
        WinInfo() : type(None), startPos(-1, -1), endPos(-1, -1), winner(ChessBoard::Empty) {}
    };
    
    explicit GameRule(QObject *parent = nullptr);
    
    // 规则检查
    bool isValidMove(const QPoint& position, const ChessBoard* board) const;
    bool checkWin(const QPoint& lastMove, const ChessBoard* board, WinInfo* winInfo = nullptr) const;
    bool isDraw(const ChessBoard* board) const;
    
    // 辅助功能
    QList<QPoint> getWinningLine(const QPoint& lastMove, const ChessBoard* board) const;
    int countConsecutive(const QPoint& position, const QPoint& direction, 
                        ChessBoard::PieceType type, const ChessBoard* board) const;

private:
    bool checkDirection(const QPoint& position, const QPoint& direction,
                       ChessBoard::PieceType type, const ChessBoard* board) const;
    QList<QPoint> getLineInDirection(const QPoint& position, const QPoint& direction,
                                    ChessBoard::PieceType type, const ChessBoard* board) const;
    
    static const QPoint DIRECTIONS[4];
    static const int WIN_COUNT = 5;
};

#endif // GAMERULE_H 