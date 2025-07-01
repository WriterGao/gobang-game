#include "GameWidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QPixmap>
#include <QFileInfo>
#include "managers/AudioManager.h"
#include "managers/ConfigManager.h"

// 定义static const成员变量
const int GameWidget::MIN_CELL_SIZE;
const int GameWidget::MAX_CELL_SIZE;
const int GameWidget::BOARD_MARGIN;

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent)
    , m_gameEngine(nullptr)
    , m_cellSize(30)
    , m_hoverPosition(-1, -1)
    , m_showCoordinates(true)
    , m_showLastMove(true)
    , m_boardColor(QColor(218, 165, 32))      // 金色棋盘
    , m_lineColor(QColor(139, 69, 19))        // 棕色线条
    , m_blackPieceColor(Qt::black)
    , m_whitePieceColor(Qt::white)
    , m_lastMoveColor(Qt::red)
    , m_hoverColor(QColor(255, 255, 0, 128))  // 半透明黄色
{
    setMouseTracking(true);
    setMinimumSize(400, 400);
}

void GameWidget::setGameEngine(GameEngine* engine)
{
    if (m_gameEngine) {
        disconnect(m_gameEngine, nullptr, this, nullptr);
    }
    
    m_gameEngine = engine;
    
    if (m_gameEngine) {
        connect(m_gameEngine, &GameEngine::moveMade,
                this, &GameWidget::onMoveMade);
        connect(m_gameEngine, &GameEngine::moveUndone,
                this, &GameWidget::onMoveUndone);
        connect(m_gameEngine, &GameEngine::gameStateChanged,
                this, &GameWidget::onGameStateChanged);
    }
    
    update();
}

void GameWidget::setShowCoordinates(bool show)
{
    if (m_showCoordinates != show) {
        m_showCoordinates = show;
        update();
    }
}

void GameWidget::setShowLastMove(bool show)
{
    if (m_showLastMove != show) {
        m_showLastMove = show;
        update();
    }
}

void GameWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // 计算棋盘区域
    m_boardRect = calculateBoardRect();
    m_cellSize = m_boardRect.width() / (ChessBoard::BOARD_SIZE - 1);
    
    // 绘制各个部分
    drawBackground(painter);
    drawBoard(painter);
    
    if (m_showCoordinates) {
        drawCoordinates(painter);
    }
    
    drawPieces(painter);
    
    if (m_showLastMove) {
        drawLastMove(painter);
    }
    
    drawHoverEffect(painter);
}

void GameWidget::mousePressEvent(QMouseEvent *event)
{
    if (!m_gameEngine || event->button() != Qt::LeftButton) {
        return;
    }
    
    QPoint boardPos = pixelToBoard(event->pos());
    if (boardPos.x() >= 0 && boardPos.y() >= 0) {
        // 如果当前玩家是人类玩家，处理点击
        Player* currentPlayer = m_gameEngine->currentPlayerObject();
        if (currentPlayer && currentPlayer->type() == Player::Human) {
            HumanPlayer* humanPlayer = dynamic_cast<HumanPlayer*>(currentPlayer);
            if (humanPlayer) {
                humanPlayer->makeMove(boardPos);
                AudioManager::instance()->playEffect(AudioManager::PiecePlaced);
            }
        }
        
        emit positionClicked(boardPos);
    }
}

void GameWidget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint boardPos = pixelToBoard(event->pos());
    if (boardPos != m_hoverPosition) {
        m_hoverPosition = boardPos;
        update();
    }
}

void GameWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    update();
}

void GameWidget::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    m_hoverPosition = QPoint(-1, -1);
    update();
}

void GameWidget::onMoveMade(const QPoint& position, ChessBoard::PieceType piece)
{
    Q_UNUSED(position)
    Q_UNUSED(piece)
    update();
}

void GameWidget::onMoveUndone(const QPoint& position)
{
    Q_UNUSED(position)
    update();
}

void GameWidget::onGameStateChanged(GameEngine::GameState state)
{
    Q_UNUSED(state)
    update();
}

void GameWidget::drawBackground(QPainter& painter)
{
    // 检查是否需要更新背景图片
    ConfigManager* configManager = ConfigManager::instance();
    QString backgroundPath = configManager->backgroundImage();
    
    if (!backgroundPath.isEmpty() && backgroundPath != m_currentBackgroundPath) {
        if (QFileInfo::exists(backgroundPath)) {
            m_backgroundPixmap.load(backgroundPath);
            m_currentBackgroundPath = backgroundPath;
        } else {
            m_backgroundPixmap = QPixmap();
            m_currentBackgroundPath.clear();
        }
    }
    
    // 绘制背景图片
    if (!m_backgroundPixmap.isNull()) {
        float opacity = configManager->backgroundOpacity();
        painter.setOpacity(opacity);
        
        // 缩放图片以适应窗口
        QPixmap scaledPixmap = m_backgroundPixmap.scaled(
            size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        
        // 居中绘制
        int x = (width() - scaledPixmap.width()) / 2;
        int y = (height() - scaledPixmap.height()) / 2;
        painter.drawPixmap(x, y, scaledPixmap);
        
        painter.setOpacity(1.0); // 恢复不透明度
    }
}

void GameWidget::drawBoard(QPainter& painter)
{
    // 绘制半透明棋盘背景
    QColor transparentBoardColor = m_boardColor;
    transparentBoardColor.setAlpha(180); // 设置透明度（0-255，180表示约70%不透明度）
    painter.fillRect(m_boardRect, transparentBoardColor);
    
    // 绘制网格线
    painter.setPen(QPen(m_lineColor, 1));
    
    // 绘制垂直线
    for (int i = 0; i < ChessBoard::BOARD_SIZE; ++i) {
        int x = m_boardRect.left() + i * m_cellSize;
        painter.drawLine(x, m_boardRect.top(), x, m_boardRect.bottom());
    }
    
    // 绘制水平线
    for (int i = 0; i < ChessBoard::BOARD_SIZE; ++i) {
        int y = m_boardRect.top() + i * m_cellSize;
        painter.drawLine(m_boardRect.left(), y, m_boardRect.right(), y);
    }
    
    // 绘制天元和星位
    painter.setBrush(m_lineColor);
    int centerX = m_boardRect.left() + 7 * m_cellSize;
    int centerY = m_boardRect.top() + 7 * m_cellSize;
    painter.drawEllipse(centerX - 3, centerY - 3, 6, 6);
}

void GameWidget::drawCoordinates(QPainter& painter)
{
    painter.setPen(m_lineColor);
    QFont font = painter.font();
    font.setPointSize(10);
    painter.setFont(font);
    
    // 绘制列标识 (A-O)
    for (int i = 0; i < ChessBoard::BOARD_SIZE; ++i) {
        int x = m_boardRect.left() + i * m_cellSize;
        QString label = QString(QChar('A' + i));
        
        painter.drawText(x - 5, m_boardRect.top() - 10, label);
        painter.drawText(x - 5, m_boardRect.bottom() + 20, label);
    }
    
    // 绘制行标识 (1-15)
    for (int i = 0; i < ChessBoard::BOARD_SIZE; ++i) {
        int y = m_boardRect.top() + i * m_cellSize;
        QString label = QString::number(15 - i);
        
        painter.drawText(m_boardRect.left() - 20, y + 5, label);
        painter.drawText(m_boardRect.right() + 10, y + 5, label);
    }
}

void GameWidget::drawPieces(QPainter& painter)
{
    if (!m_gameEngine) {
        return;
    }
    
    ChessBoard* board = m_gameEngine->chessBoard();
    if (!board) {
        return;
    }
    
    int pieceRadius = qMax(3, m_cellSize / 3);
    
    for (int row = 0; row < ChessBoard::BOARD_SIZE; ++row) {
        for (int col = 0; col < ChessBoard::BOARD_SIZE; ++col) {
            ChessBoard::PieceType piece = board->pieceAt(row, col);
            if (piece != ChessBoard::Empty) {
                QPoint pixelPos = boardToPixel(QPoint(col, row));
                
                // 设置棋子颜色
                if (piece == ChessBoard::Black) {
                    painter.setBrush(m_blackPieceColor);
                    painter.setPen(QPen(Qt::gray, 1));
                } else {
                    painter.setBrush(m_whitePieceColor);
                    painter.setPen(QPen(Qt::black, 1));
                }
                
                painter.drawEllipse(pixelPos.x() - pieceRadius, pixelPos.y() - pieceRadius,
                                   pieceRadius * 2, pieceRadius * 2);
            }
        }
    }
}

void GameWidget::drawLastMove(QPainter& painter)
{
    if (!m_gameEngine) {
        return;
    }
    
    ChessBoard* board = m_gameEngine->chessBoard();
    if (!board || !board->hasHistory()) {
        return;
    }
    
    QPoint lastMove = board->lastMove();
    QPoint pixelPos = boardToPixel(lastMove);
    
    painter.setPen(QPen(m_lastMoveColor, 2));
    painter.setBrush(Qt::NoBrush);
    
    int radius = qMax(5, m_cellSize / 3 + 2);
    painter.drawEllipse(pixelPos.x() - radius, pixelPos.y() - radius,
                       radius * 2, radius * 2);
}

void GameWidget::drawHoverEffect(QPainter& painter)
{
    if (!m_gameEngine || m_hoverPosition.x() < 0 || m_hoverPosition.y() < 0) {
        return;
    }
    
    // 只在空位置显示悬停效果
    ChessBoard* board = m_gameEngine->chessBoard();
    if (!board || !board->isEmpty(m_hoverPosition)) {
        return;
    }
    
    // 只在游戏进行中且轮到人类玩家时显示
    if (m_gameEngine->gameState() != GameEngine::Playing) {
        return;
    }
    
    Player* currentPlayer = m_gameEngine->currentPlayerObject();
    if (!currentPlayer || currentPlayer->type() != Player::Human) {
        return;
    }
    
    QPoint pixelPos = boardToPixel(m_hoverPosition);
    int radius = qMax(3, m_cellSize / 4);
    
    painter.setBrush(m_hoverColor);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(pixelPos.x() - radius, pixelPos.y() - radius,
                       radius * 2, radius * 2);
}

QPoint GameWidget::pixelToBoard(const QPoint& pixel) const
{
    if (!m_boardRect.contains(pixel)) {
        return QPoint(-1, -1);
    }
    
    int col = qRound((pixel.x() - m_boardRect.left()) / (double)m_cellSize);
    int row = qRound((pixel.y() - m_boardRect.top()) / (double)m_cellSize);
    
    if (col >= 0 && col < ChessBoard::BOARD_SIZE && 
        row >= 0 && row < ChessBoard::BOARD_SIZE) {
        return QPoint(col, row);
    }
    
    return QPoint(-1, -1);
}

QPoint GameWidget::boardToPixel(const QPoint& board) const
{
    int x = m_boardRect.left() + board.x() * m_cellSize;
    int y = m_boardRect.top() + board.y() * m_cellSize;
    return QPoint(x, y);
}

QRect GameWidget::calculateBoardRect() const
{
    int availableWidth = width() - 2 * BOARD_MARGIN;
    int availableHeight = height() - 2 * BOARD_MARGIN;
    int boardSize = qMin(availableWidth, availableHeight);
    
    // 确保格子大小在合理范围内
    int cellSize = boardSize / (ChessBoard::BOARD_SIZE - 1);
    cellSize = qBound(MIN_CELL_SIZE, cellSize, MAX_CELL_SIZE);
    boardSize = cellSize * (ChessBoard::BOARD_SIZE - 1);
    
    int x = (width() - boardSize) / 2;
    int y = (height() - boardSize) / 2;
    
    return QRect(x, y, boardSize, boardSize);
} 