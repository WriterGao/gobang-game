#include "ChessBoard.h"
#include <QDataStream>

ChessBoard::ChessBoard(QObject *parent)
    : QObject(parent)
{
    clearBoard();
}

bool ChessBoard::placePiece(const QPoint& position, PieceType type)
{
    if (!isValidPosition(position) || !isEmpty(position) || type == Empty) {
        return false;
    }
    
    m_board[position.y()][position.x()] = type;
    pushMove(position);
    
    emit pieceAdded(position, type);
    return true;
}

bool ChessBoard::removePiece(const QPoint& position)
{
    if (!isValidPosition(position) || isEmpty(position)) {
        return false;
    }
    
    m_board[position.y()][position.x()] = Empty;
    emit pieceRemoved(position);
    return true;
}

void ChessBoard::clearBoard()
{
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            m_board[row][col] = Empty;
        }
    }
    m_moveHistory.clear();
    emit boardCleared();
}

ChessBoard::PieceType ChessBoard::pieceAt(const QPoint& position) const
{
    return pieceAt(position.y(), position.x());
}

ChessBoard::PieceType ChessBoard::pieceAt(int row, int col) const
{
    if (!isInBounds(row, col)) {
        return Empty;
    }
    return m_board[row][col];
}

bool ChessBoard::isEmpty(const QPoint& position) const
{
    return pieceAt(position) == Empty;
}

bool ChessBoard::isValidPosition(const QPoint& position) const
{
    return isInBounds(position.y(), position.x());
}

bool ChessBoard::isFull() const
{
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (m_board[row][col] == Empty) {
                return false;
            }
        }
    }
    return true;
}

QList<QPoint> ChessBoard::moveHistory() const
{
    return m_moveHistory;
}

QPoint ChessBoard::lastMove() const
{
    return hasHistory() ? m_moveHistory.last() : QPoint(-1, -1);
}

bool ChessBoard::hasHistory() const
{
    return !m_moveHistory.isEmpty();
}

void ChessBoard::pushMove(const QPoint& position)
{
    m_moveHistory.append(position);
}

QPoint ChessBoard::popMove()
{
    if (!hasHistory()) {
        return QPoint(-1, -1);
    }
    
    QPoint lastPosition = m_moveHistory.takeLast();
    removePiece(lastPosition);
    return lastPosition;
}

void ChessBoard::getBoardState(PieceType board[BOARD_SIZE][BOARD_SIZE]) const
{
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            board[row][col] = m_board[row][col];
        }
    }
}

void ChessBoard::setBoardState(const PieceType board[BOARD_SIZE][BOARD_SIZE])
{
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            m_board[row][col] = board[row][col];
        }
    }
}

QByteArray ChessBoard::serialize() const
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    
    // 序列化棋盘状态
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            stream << static_cast<int>(m_board[row][col]);
        }
    }
    
    // 序列化移动历史
    stream << m_moveHistory.size();
    for (const QPoint& move : m_moveHistory) {
        stream << move;
    }
    
    return data;
}

bool ChessBoard::deserialize(const QByteArray& data)
{
    QDataStream stream(data);
    
    try {
        // 反序列化棋盘状态
        for (int row = 0; row < BOARD_SIZE; ++row) {
            for (int col = 0; col < BOARD_SIZE; ++col) {
                int pieceValue;
                stream >> pieceValue;
                m_board[row][col] = static_cast<PieceType>(pieceValue);
            }
        }
        
        // 反序列化移动历史
        int historySize;
        stream >> historySize;
        m_moveHistory.clear();
        m_moveHistory.reserve(historySize);
        
        for (int i = 0; i < historySize; ++i) {
            QPoint move;
            stream >> move;
            m_moveHistory.append(move);
        }
        
        return true;
    } catch (...) {
        return false;
    }
}

bool ChessBoard::isInBounds(int row, int col) const
{
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
} 