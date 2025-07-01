#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QObject>
#include <QPoint>
#include <QList>
#include <QByteArray>

class ChessBoard : public QObject
{
    Q_OBJECT

public:
    enum PieceType { Empty = 0, Black = 1, White = 2 };
    static const int BOARD_SIZE = 15;
    
    explicit ChessBoard(QObject *parent = nullptr);
    
    // 棋盘操作
    bool placePiece(const QPoint& position, PieceType type);
    bool removePiece(const QPoint& position);
    void clearBoard();
    
    // 状态查询
    PieceType pieceAt(const QPoint& position) const;
    PieceType pieceAt(int row, int col) const;
    bool isEmpty(const QPoint& position) const;
    bool isValidPosition(const QPoint& position) const;
    bool isFull() const;
    
    // 历史管理
    QList<QPoint> moveHistory() const;
    QPoint lastMove() const;
    bool hasHistory() const;
    void pushMove(const QPoint& position);
    QPoint popMove();
    
    // 数据导出/导入
    void getBoardState(PieceType board[BOARD_SIZE][BOARD_SIZE]) const;
    void setBoardState(const PieceType board[BOARD_SIZE][BOARD_SIZE]);
    QByteArray serialize() const;
    bool deserialize(const QByteArray& data);

signals:
    void pieceAdded(const QPoint& position, PieceType type);
    void pieceRemoved(const QPoint& position);
    void boardCleared();

private:
    bool isInBounds(int row, int col) const;
    
    PieceType m_board[BOARD_SIZE][BOARD_SIZE];
    QList<QPoint> m_moveHistory;
};

#endif // CHESSBOARD_H 