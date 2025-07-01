#include "GameEngine.h"
#include "ai/MinimaxAI.h"

GameEngine::GameEngine(QObject *parent)
    : QObject(parent)
    , m_board(new ChessBoard(this))
    , m_rule(new GameRule(this))
    , m_players{nullptr, nullptr}
    , m_state(Ready)
    , m_mode(PvP)
    , m_currentPlayerIndex(0)
    , m_winner(ChessBoard::Empty)
    , m_undoCount(0)
    , m_aiDifficulty(2)
{
    setupPlayers();
}

GameEngine::~GameEngine()
{
    for (int i = 0; i < 2; ++i) {
        delete m_players[i];
    }
}

void GameEngine::startNewGame(GameMode mode)
{
    if (m_state == Playing) {
        endGame();
    }
    
    m_mode = mode;
    m_state = Playing;
    m_currentPlayerIndex = 0; // 黑方先手
    m_winner = ChessBoard::Empty;
    m_undoCount = 0;
    
    // 清空棋盘
    m_board->clearBoard();
    
    // 重新设置玩家
    setupPlayers();
    
    // 启动计时器
    m_gameTimer.start();
    
    emit gameStateChanged(m_state);
    emit playerChanged(currentPlayer());
    
    // 如果当前玩家是AI，请求AI下棋
    requestPlayerMove();
}

void GameEngine::pauseGame()
{
    if (m_state == Playing) {
        m_state = Paused;
        emit gameStateChanged(m_state);
        
        // 如果AI正在思考，取消思考
        Player* current = currentPlayerObject();
        if (current && current->type() == Player::AI) {
            current->cancelMove();
        }
    }
}

void GameEngine::resumeGame()
{
    if (m_state == Paused) {
        m_state = Playing;
        emit gameStateChanged(m_state);
        
        // 重新请求当前玩家下棋
        requestPlayerMove();
    }
}

void GameEngine::endGame()
{
    if (m_state == Playing || m_state == Paused) {
        m_state = Finished;
        emit gameStateChanged(m_state);
        
        // 取消所有玩家的操作
        for (int i = 0; i < 2; ++i) {
            if (m_players[i]) {
                m_players[i]->cancelMove();
            }
        }
    }
}

void GameEngine::restartGame()
{
    startNewGame(m_mode);
}

bool GameEngine::makeMove(const QPoint& position)
{
    if (m_state != Playing) {
        emit errorOccurred("游戏未进行中");
        return false;
    }
    
    // 验证移动合法性
    if (!m_rule->isValidMove(position, m_board)) {
        emit errorOccurred("非法移动");
        return false;
    }
    
    ChessBoard::PieceType currentPiece = currentPlayer();
    
    // 在棋盘上放置棋子
    if (!m_board->placePiece(position, currentPiece)) {
        emit errorOccurred("无法放置棋子");
        return false;
    }
    
    emit moveMade(position, currentPiece);
    
    // 检查游戏是否结束
    checkGameEnd();
    
    if (m_state == Playing) {
        // 切换玩家
        switchPlayer();
        
        // 请求下一个玩家下棋
        requestPlayerMove();
    }
    
    return true;
}

bool GameEngine::undoMove()
{
    if (!canUndo()) {
        return false;
    }
    
    QPoint lastMove = m_board->popMove();
    if (lastMove.x() >= 0 && lastMove.y() >= 0) {
        m_undoCount++;
        
        // 切换回上一个玩家
        m_currentPlayerIndex = (m_currentPlayerIndex + 1) % 2;
        
        emit moveUndone(lastMove);
        emit playerChanged(currentPlayer());
        
        // 如果是人机对战，可能需要悔棋两步
        if (m_mode == PvC && m_board->hasHistory()) {
            // 悔棋AI的一步
            QPoint aiMove = m_board->popMove();
            if (aiMove.x() >= 0 && aiMove.y() >= 0) {
                emit moveUndone(aiMove);
            }
        }
        
        // 重新请求当前玩家下棋
        requestPlayerMove();
        
        return true;
    }
    
    return false;
}

bool GameEngine::canUndo() const
{
    return m_state == Playing && m_board->hasHistory();
}

ChessBoard::PieceType GameEngine::currentPlayer() const
{
    return m_currentPlayerIndex == 0 ? ChessBoard::Black : ChessBoard::White;
}

int GameEngine::moveCount() const
{
    return m_board->moveHistory().size();
}

qint64 GameEngine::elapsedTime() const
{
    if (m_state == Playing || m_state == Paused || m_state == Finished) {
        return m_gameTimer.elapsed();
    }
    return 0;
}

Player* GameEngine::player(int index) const
{
    if (index >= 0 && index < 2) {
        return m_players[index];
    }
    return nullptr;
}

Player* GameEngine::currentPlayerObject() const
{
    return m_players[m_currentPlayerIndex];
}

void GameEngine::setGameMode(GameMode mode)
{
    if (m_state == Ready) {
        m_mode = mode;
        setupPlayers();
    }
}

void GameEngine::setAIDifficulty(int difficulty)
{
    m_aiDifficulty = difficulty;
    
    // 如果当前有AI玩家，更新其难度
    for (int i = 0; i < 2; ++i) {
        if (m_players[i] && m_players[i]->type() == Player::AI) {
            auto aiPlayer = dynamic_cast<AIPlayer*>(m_players[i]);
            if (aiPlayer) {
                aiPlayer->setDifficulty(difficulty);
            }
        }
    }
}

void GameEngine::onPlayerMoveReady(const QPoint& position)
{
    Player* sender = qobject_cast<Player*>(this->sender());
    if (sender == currentPlayerObject()) {
        makeMove(position);
    }
}

void GameEngine::onPlayerMoveCancelled()
{
    // 处理玩家取消移动
}

void GameEngine::initializeGame()
{
    m_currentPlayerIndex = 0;
    m_winner = ChessBoard::Empty;
    m_undoCount = 0;
    m_board->clearBoard();
}

void GameEngine::setupPlayers()
{
    // 清理现有玩家
    for (int i = 0; i < 2; ++i) {
        if (m_players[i]) {
            disconnect(m_players[i], nullptr, this, nullptr);
            delete m_players[i];
            m_players[i] = nullptr;
        }
    }
    
    // 创建新玩家
    switch (m_mode) {
        case PvP:
            // 人人对战
            m_players[0] = new HumanPlayer(ChessBoard::Black, this);
            m_players[1] = new HumanPlayer(ChessBoard::White, this);
            break;
            
        case PvC:
            // 人机对战
            m_players[0] = new HumanPlayer(ChessBoard::Black, this);
            m_players[1] = new MinimaxAI(ChessBoard::White, m_aiDifficulty, this);
            break;
            
        case Network:
            // 网络对战 (暂未实现)
            m_players[0] = new HumanPlayer(ChessBoard::Black, this);
            m_players[1] = new HumanPlayer(ChessBoard::White, this);
            break;
    }
    
    // 连接玩家信号
    for (int i = 0; i < 2; ++i) {
        if (m_players[i]) {
            connect(m_players[i], &Player::moveReady,
                    this, &GameEngine::onPlayerMoveReady);
            connect(m_players[i], &Player::moveCancelled,
                    this, &GameEngine::onPlayerMoveCancelled);
        }
    }
}

void GameEngine::switchPlayer()
{
    m_currentPlayerIndex = (m_currentPlayerIndex + 1) % 2;
    emit playerChanged(currentPlayer());
}

void GameEngine::checkGameEnd()
{
    QPoint lastMove = m_board->lastMove();
    if (lastMove.x() >= 0 && lastMove.y() >= 0) {
        // 检查是否有玩家获胜
        if (m_rule->checkWin(lastMove, m_board)) {
            m_winner = m_board->pieceAt(lastMove);
            m_state = Finished;
            emit gameWon(m_winner);
            emit gameStateChanged(m_state);
            return;
        }
    }
    
    // 检查是否平局
    if (m_rule->isDraw(m_board)) {
        m_state = Finished;
        emit gameDraw();
        emit gameStateChanged(m_state);
    }
}

void GameEngine::notifyGameEnd()
{
    m_state = Finished;
    emit gameStateChanged(m_state);
}

void GameEngine::requestPlayerMove()
{
    if (m_state != Playing) {
        return;
    }
    
    Player* current = currentPlayerObject();
    if (current) {
        current->requestMove(m_board);
    }
} 