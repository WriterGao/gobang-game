#include "AIPlayer.h"
#include <QFuture>
#include <QtConcurrent>

AIPlayer::AIPlayer(ChessBoard::PieceType pieceType, int difficulty, QObject *parent)
    : Player(pieceType, parent)
    , m_watcher(new QFutureWatcher<QPoint>(this))
    , m_thinking(false)
    , m_difficulty(difficulty)
{
    connect(m_watcher, &QFutureWatcher<QPoint>::finished, 
            this, &AIPlayer::onCalculationFinished);
}

AIPlayer::~AIPlayer()
{
    cancelMove();
}

void AIPlayer::requestMove(const ChessBoard* board)
{
    if (m_thinking) {
        return;
    }
    
    m_thinking = true;
    
    // 在独立线程中计算最佳移动
    QFuture<QPoint> future = QtConcurrent::run([this, board]() {
        return calculateMove(board);
    });
    
    m_watcher->setFuture(future);
}

void AIPlayer::cancelMove()
{
    if (m_thinking && m_watcher->isRunning()) {
        m_watcher->cancel();
        m_watcher->waitForFinished();
        m_thinking = false;
        emit moveCancelled();
    }
}

void AIPlayer::onCalculationFinished()
{
    if (m_watcher->isCanceled()) {
        m_thinking = false;
        return;
    }
    
    QPoint move = m_watcher->result();
    m_thinking = false;
    
    if (move.x() >= 0 && move.y() >= 0) {
        emit moveReady(move);
    }
} 