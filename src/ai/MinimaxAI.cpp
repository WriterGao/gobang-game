#include "MinimaxAI.h"
#include <QRandomGenerator>
#include <algorithm>

MinimaxAI::MinimaxAI(ChessBoard::PieceType pieceType, int difficulty, QObject *parent)
    : AIPlayer(pieceType, difficulty, parent)
    , m_rule(new GameRule(this))
{
    setName(QString("AI_%1").arg(pieceType == ChessBoard::Black ? "黑" : "白"));
}

QPoint MinimaxAI::calculateMove(const ChessBoard* board)
{
    if (!board || board->moveHistory().isEmpty()) {
        // 如果是第一步，下在中心位置
        return QPoint(7, 7);
    }
    
    // 创建棋盘副本进行计算
    ChessBoard* tempBoard = new ChessBoard();
    ChessBoard::PieceType tempBoardData[ChessBoard::BOARD_SIZE][ChessBoard::BOARD_SIZE];
    board->getBoardState(tempBoardData);
    tempBoard->setBoardState(tempBoardData);
    
    MoveScore bestMove = minimax(tempBoard, getMaxDepth(), true);
    
    delete tempBoard;
    
    // 如果没有找到好的移动，随机选择一个
    if (bestMove.position.x() < 0 || bestMove.position.y() < 0) {
        QList<QPoint> candidates = generateCandidateMoves(board);
        if (!candidates.isEmpty()) {
            int randomIndex = QRandomGenerator::global()->bounded(candidates.size());
            return candidates[randomIndex];
        }
    }
    
    return bestMove.position;
}

MinimaxAI::MoveScore MinimaxAI::minimax(ChessBoard* board, int depth, bool isMaximizing, int alpha, int beta)
{
    // 检查游戏结束或达到最大深度
    if (depth == 0 || board->isFull()) {
        return MoveScore(QPoint(-1, -1), evaluateBoard(board));
    }
    
    QList<QPoint> candidates = generateCandidateMoves(board);
    if (candidates.isEmpty()) {
        return MoveScore(QPoint(-1, -1), evaluateBoard(board));
    }
    
    ChessBoard::PieceType currentPlayer = isMaximizing ? m_pieceType : 
        (m_pieceType == ChessBoard::Black ? ChessBoard::White : ChessBoard::Black);
    
    MoveScore bestMove(QPoint(-1, -1), isMaximizing ? INT_MIN : INT_MAX);
    
    for (const QPoint& move : candidates) {
        // 尝试这一步
        board->placePiece(move, currentPlayer);
        
        // 检查是否获胜
        if (m_rule->checkWin(move, board)) {
            board->removePiece(move);
            int score = isMaximizing ? WIN_SCORE : -WIN_SCORE;
            return MoveScore(move, score);
        }
        
        // 递归搜索
        MoveScore score = minimax(board, depth - 1, !isMaximizing, alpha, beta);
        
        // 撤销这一步
        board->removePiece(move);
        
        if (isMaximizing) {
            if (score.score > bestMove.score) {
                bestMove = MoveScore(move, score.score);
            }
            alpha = std::max(alpha, score.score);
        } else {
            if (score.score < bestMove.score) {
                bestMove = MoveScore(move, score.score);
            }
            beta = std::min(beta, score.score);
        }
        
        // Alpha-Beta剪枝
        if (beta <= alpha) {
            break;
        }
    }
    
    return bestMove;
}

int MinimaxAI::evaluateBoard(const ChessBoard* board) const
{
    int score = 0;
    
    // 评估每个位置
    for (int row = 0; row < ChessBoard::BOARD_SIZE; ++row) {
        for (int col = 0; col < ChessBoard::BOARD_SIZE; ++col) {
            QPoint pos(col, row);
            ChessBoard::PieceType piece = board->pieceAt(pos);
            
            if (piece != ChessBoard::Empty) {
                int posScore = evaluatePosition(pos, piece, board);
                score += (piece == m_pieceType) ? posScore : -posScore;
            }
        }
    }
    
    return score;
}

int MinimaxAI::evaluatePosition(const QPoint& position, ChessBoard::PieceType type, const ChessBoard* board) const
{
    int score = 0;
    
    // 四个方向的评估
    static const QPoint directions[4] = {
        QPoint(1, 0),   // 水平
        QPoint(0, 1),   // 垂直
        QPoint(1, 1),   // 主对角线
        QPoint(1, -1)   // 反对角线
    };
    
    for (int i = 0; i < 4; ++i) {
        score += evaluateLine(position, directions[i], type, board);
    }
    
    return score;
}

int MinimaxAI::evaluateLine(const QPoint& position, const QPoint& direction, 
                           ChessBoard::PieceType type, const ChessBoard* board) const
{
    int count = 1; // 包含当前位置
    int emptyCount = 0;
    
    // 向正方向搜索
    QPoint pos = position + direction;
    while (board->isValidPosition(pos)) {
        ChessBoard::PieceType piece = board->pieceAt(pos);
        if (piece == type) {
            count++;
        } else if (piece == ChessBoard::Empty) {
            emptyCount++;
            break;
        } else {
            break;
        }
        pos += direction;
    }
    
    // 向负方向搜索
    pos = position - direction;
    while (board->isValidPosition(pos)) {
        ChessBoard::PieceType piece = board->pieceAt(pos);
        if (piece == type) {
            count++;
        } else if (piece == ChessBoard::Empty) {
            emptyCount++;
            break;
        } else {
            break;
        }
        pos -= direction;
    }
    
    // 根据连子数量和开放性评分
    if (count >= 5) {
        return WIN_SCORE;
    } else if (count == 4) {
        return emptyCount > 0 ? FOUR_SCORE : BLOCK_FOUR_SCORE;
    } else if (count == 3) {
        return emptyCount > 0 ? THREE_SCORE : BLOCK_THREE_SCORE;
    } else if (count == 2) {
        return emptyCount > 0 ? TWO_SCORE : 0;
    } else {
        return emptyCount > 0 ? ONE_SCORE : 0;
    }
}

QList<QPoint> MinimaxAI::generateCandidateMoves(const ChessBoard* board) const
{
    QList<QPoint> candidates;
    QSet<QPoint> candidateSet;
    
    // 收集所有已下棋子周围的空位置
    for (const QPoint& move : board->moveHistory()) {
        QList<QPoint> neighbors = getNeighborPositions(move, 2);
        for (const QPoint& neighbor : neighbors) {
            if (board->isEmpty(neighbor) && !candidateSet.contains(neighbor)) {
                candidates.append(neighbor);
                candidateSet.insert(neighbor);
            }
        }
    }
    
    // 如果没有候选位置，返回中心附近的位置
    if (candidates.isEmpty()) {
        for (int row = 6; row <= 8; ++row) {
            for (int col = 6; col <= 8; ++col) {
                QPoint pos(col, row);
                if (board->isEmpty(pos)) {
                    candidates.append(pos);
                }
            }
        }
    }
    
    // 按重要性排序候选位置
    std::sort(candidates.begin(), candidates.end(), [this, board](const QPoint& a, const QPoint& b) {
        return evaluatePosition(a, m_pieceType, board) > evaluatePosition(b, m_pieceType, board);
    });
    
    // 限制候选数量以提高性能
    if (candidates.size() > 20) {
        candidates = candidates.mid(0, 20);
    }
    
    return candidates;
}

QList<QPoint> MinimaxAI::getNeighborPositions(const QPoint& position, int radius) const
{
    QList<QPoint> neighbors;
    
    for (int dx = -radius; dx <= radius; ++dx) {
        for (int dy = -radius; dy <= radius; ++dy) {
            if (dx == 0 && dy == 0) continue;
            
            QPoint neighbor(position.x() + dx, position.y() + dy);
            if (neighbor.x() >= 0 && neighbor.x() < ChessBoard::BOARD_SIZE &&
                neighbor.y() >= 0 && neighbor.y() < ChessBoard::BOARD_SIZE) {
                neighbors.append(neighbor);
            }
        }
    }
    
    return neighbors;
}

bool MinimaxAI::isImportantPosition(const QPoint& position, const ChessBoard* board) const
{
    // 检查该位置是否在已有棋子附近
    QList<QPoint> neighbors = getNeighborPositions(position, 1);
    for (const QPoint& neighbor : neighbors) {
        if (!board->isEmpty(neighbor)) {
            return true;
        }
    }
    return false;
}

int MinimaxAI::getMaxDepth() const
{
    switch (difficulty()) {
        case 1: return 2;  // 简单
        case 2: return 4;  // 中等
        case 3: return 6;  // 困难
        default: return 4;
    }
} 