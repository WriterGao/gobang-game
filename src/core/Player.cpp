#include "Player.h"

Player::Player(ChessBoard::PieceType pieceType, QObject *parent)
    : QObject(parent)
    , m_pieceType(pieceType)
    , m_name(pieceType == ChessBoard::Black ? "黑方" : "白方")
{
}

// HumanPlayer 实现
HumanPlayer::HumanPlayer(ChessBoard::PieceType pieceType, QObject *parent)
    : Player(pieceType, parent)
    , m_waitingForMove(false)
{
}

void HumanPlayer::requestMove(const ChessBoard* board)
{
    Q_UNUSED(board)
    m_waitingForMove = true;
    // 人类玩家不需要自动生成移动，等待用户点击
}

void HumanPlayer::makeMove(const QPoint& position)
{
    if (m_waitingForMove) {
        m_waitingForMove = false;
        emit moveReady(position);
    }
} 