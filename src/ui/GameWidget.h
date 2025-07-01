#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QPoint>
#include <QRect>
#include <QColor>
#include "core/GameEngine.h"

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameWidget(QWidget *parent = nullptr);
    
    void setGameEngine(GameEngine* engine);
    GameEngine* gameEngine() const { return m_gameEngine; }
    
    // 显示设置
    void setShowCoordinates(bool show);
    bool showCoordinates() const { return m_showCoordinates; }
    
    void setShowLastMove(bool show);
    bool showLastMove() const { return m_showLastMove; }

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void leaveEvent(QEvent *event) override;

private slots:
    void onMoveMade(const QPoint& position, ChessBoard::PieceType piece);
    void onMoveUndone(const QPoint& position);
    void onGameStateChanged(GameEngine::GameState state);

signals:
    void positionClicked(const QPoint& position);

private:
    void drawBackground(QPainter& painter);
    void drawBoard(QPainter& painter);
    void drawCoordinates(QPainter& painter);
    void drawPieces(QPainter& painter);
    void drawLastMove(QPainter& painter);
    void drawHoverEffect(QPainter& painter);
    
    QPoint pixelToBoard(const QPoint& pixel) const;
    QPoint boardToPixel(const QPoint& board) const;
    QRect calculateBoardRect() const;
    
    GameEngine* m_gameEngine;
    
    // 绘制相关
    QRect m_boardRect;
    int m_cellSize;
    QPoint m_hoverPosition;
    bool m_showCoordinates;
    bool m_showLastMove;
    
    // 样式
    QColor m_boardColor;
    QColor m_lineColor;
    QColor m_blackPieceColor;
    QColor m_whitePieceColor;
    QColor m_lastMoveColor;
    QColor m_hoverColor;
    
    static const int MIN_CELL_SIZE = 20;
    static const int MAX_CELL_SIZE = 50;
    static const int BOARD_MARGIN = 30;
    
    // 背景图片
    QPixmap m_backgroundPixmap;
    QString m_currentBackgroundPath;
};

#endif // GAMEWIDGET_H 