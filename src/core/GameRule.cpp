#include "GameRule.h"

// 定义四个检查方向：水平、垂直、主对角线、反对角线
const QPoint GameRule::DIRECTIONS[4] = {
    QPoint(1, 0),   // 水平
    QPoint(0, 1),   // 垂直
    QPoint(1, 1),   // 主对角线
    QPoint(1, -1)   // 反对角线
};

GameRule::GameRule(QObject *parent)
    : QObject(parent)
{
}

bool GameRule::isValidMove(const QPoint& position, const ChessBoard* board) const
{
    if (!board) {
        return false;
    }
    
    return board->isValidPosition(position) && board->isEmpty(position);
}

bool GameRule::checkWin(const QPoint& lastMove, const ChessBoard* board, WinInfo* winInfo) const
{
    if (!board || !board->isValidPosition(lastMove)) {
        return false;
    }
    
    ChessBoard::PieceType piece = board->pieceAt(lastMove);
    if (piece == ChessBoard::Empty) {
        return false;
    }
    
    // 检查四个方向
    for (int i = 0; i < 4; ++i) {
        if (checkDirection(lastMove, DIRECTIONS[i], piece, board)) {
            if (winInfo) {
                winInfo->type = static_cast<WinType>(i + 1);
                winInfo->winner = piece;
                
                // 找到获胜线的起始和结束位置
                QList<QPoint> line = getLineInDirection(lastMove, DIRECTIONS[i], piece, board);
                if (!line.isEmpty()) {
                    winInfo->startPos = line.first();
                    winInfo->endPos = line.last();
                }
            }
            return true;
        }
    }
    
    return false;
}

bool GameRule::isDraw(const ChessBoard* board) const
{
    if (!board) {
        return false;
    }
    
    return board->isFull();
}

QList<QPoint> GameRule::getWinningLine(const QPoint& lastMove, const ChessBoard* board) const
{
    if (!board || !board->isValidPosition(lastMove)) {
        return QList<QPoint>();
    }
    
    ChessBoard::PieceType piece = board->pieceAt(lastMove);
    if (piece == ChessBoard::Empty) {
        return QList<QPoint>();
    }
    
    // 检查四个方向，找到获胜线
    for (int i = 0; i < 4; ++i) {
        if (checkDirection(lastMove, DIRECTIONS[i], piece, board)) {
            return getLineInDirection(lastMove, DIRECTIONS[i], piece, board);
        }
    }
    
    return QList<QPoint>();
}

int GameRule::countConsecutive(const QPoint& position, const QPoint& direction, 
                              ChessBoard::PieceType type, const ChessBoard* board) const
{
    if (!board || type == ChessBoard::Empty) {
        return 0;
    }
    
    int count = 0;
    QPoint current = position;
    
    // 向正方向计算
    while (board->isValidPosition(current) && board->pieceAt(current) == type) {
        count++;
        current += direction;
    }
    
    // 向负方向计算
    current = position - direction;
    while (board->isValidPosition(current) && board->pieceAt(current) == type) {
        count++;
        current -= direction;
    }
    
    return count;
}

bool GameRule::checkDirection(const QPoint& position, const QPoint& direction,
                             ChessBoard::PieceType type, const ChessBoard* board) const
{
    return countConsecutive(position, direction, type, board) >= WIN_COUNT;
}

QList<QPoint> GameRule::getLineInDirection(const QPoint& position, const QPoint& direction,
                                          ChessBoard::PieceType type, const ChessBoard* board) const
{
    QList<QPoint> line;
    
    if (!board || type == ChessBoard::Empty) {
        return line;
    }
    
    // 向负方向找到起始点
    QPoint start = position;
    while (board->isValidPosition(start - direction) && 
           board->pieceAt(start - direction) == type) {
        start -= direction;
    }
    
    // 从起始点向正方向收集所有相同类型的棋子
    QPoint current = start;
    while (board->isValidPosition(current) && board->pieceAt(current) == type) {
        line.append(current);
        current += direction;
    }
    
    return line;
} 