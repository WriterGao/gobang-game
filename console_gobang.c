#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BOARD_SIZE 15

typedef struct {
    char board[BOARD_SIZE][BOARD_SIZE];
    char currentPlayer;
    int moveCount;
} Game;

void initGame(Game* game) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            game->board[i][j] = '.';
        }
    }
    game->currentPlayer = 'X';
    game->moveCount = 0;
}

void printBoard(Game* game) {
    printf("\n   ");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%2d ", i);
    }
    printf("\n");
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%2d ", i);
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf(" %c ", game->board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

bool isValidMove(Game* game, int row, int col) {
    return row >= 0 && row < BOARD_SIZE && 
           col >= 0 && col < BOARD_SIZE && 
           game->board[row][col] == '.';
}

bool makeMove(Game* game, int row, int col) {
    if (!isValidMove(game, row, col)) {
        return false;
    }
    
    game->board[row][col] = game->currentPlayer;
    game->moveCount++;
    return true;
}

bool checkWin(Game* game, int row, int col) {
    char player = game->board[row][col];
    int directions[4][2] = {{0,1}, {1,0}, {1,1}, {1,-1}};
    
    for (int d = 0; d < 4; d++) {
        int count = 1;
        int dx = directions[d][0];
        int dy = directions[d][1];
        
        // 正方向检查
        for (int i = 1; i < 5; i++) {
            int newRow = row + i * dx;
            int newCol = col + i * dy;
            if (newRow >= 0 && newRow < BOARD_SIZE && 
                newCol >= 0 && newCol < BOARD_SIZE &&
                game->board[newRow][newCol] == player) {
                count++;
            } else {
                break;
            }
        }
        
        // 负方向检查
        for (int i = 1; i < 5; i++) {
            int newRow = row - i * dx;
            int newCol = col - i * dy;
            if (newRow >= 0 && newRow < BOARD_SIZE && 
                newCol >= 0 && newCol < BOARD_SIZE &&
                game->board[newRow][newCol] == player) {
                count++;
            } else {
                break;
            }
        }
        
        if (count >= 5) {
            return true;
        }
    }
    return false;
}

void switchPlayer(Game* game) {
    game->currentPlayer = (game->currentPlayer == 'X') ? 'O' : 'X';
}

int main() {
    Game game;
    initGame(&game);
    
    printf("🎮 欢迎来到五子棋游戏！\n");
    printf("==========================================\n");
    printf("游戏规则：\n");
    printf("• X 先手（黑棋），O 后手（白棋）\n");
    printf("• 率先连成5子者获胜\n");
    printf("• 输入格式：行 列 (例如: 7 7)\n");
    printf("• 输入 -1 -1 退出游戏\n");
    printf("==========================================\n\n");
    
    while (true) {
        printBoard(&game);
        printf("轮到玩家 %c 下棋 (第%d步)，请输入坐标: ", 
               game.currentPlayer, game.moveCount + 1);
        
        int row, col;
        if (scanf("%d %d", &row, &col) != 2) {
            printf("❌ 输入格式错误，请重新输入！\n");
            while (getchar() != '\n'); // 清理输入缓冲区
            continue;
        }
        
        if (row == -1 && col == -1) {
            printf("游戏结束！感谢您的游玩！\n");
            break;
        }
        
        if (!makeMove(&game, row, col)) {
            printf("❌ 无效的移动，请重新输入！\n");
            continue;
        }
        
        if (checkWin(&game, row, col)) {
            printBoard(&game);
            printf("🎉🎉🎉 恭喜玩家 %c 获胜！🎉🎉🎉\n", game.currentPlayer);
            printf("总共用了 %d 步\n", game.moveCount);
            break;
        }
        
        if (game.moveCount >= BOARD_SIZE * BOARD_SIZE) {
            printBoard(&game);
            printf("🤝 平局！棋盘已满。\n");
            break;
        }
        
        switchPlayer(&game);
    }
    
    return 0;
} 