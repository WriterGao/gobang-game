#include <iostream>
#include <vector>
#include <iomanip>

class SimpleGobang {
private:
    static const int BOARD_SIZE = 15;
    std::vector<std::vector<char>> board;
    char currentPlayer;
    
public:
    SimpleGobang() : board(BOARD_SIZE, std::vector<char>(BOARD_SIZE, '.')), currentPlayer('X') {}
    
    void printBoard() {
        std::cout << "   ";
        for (int i = 0; i < BOARD_SIZE; ++i) {
            std::cout << std::setw(2) << i << " ";
        }
        std::cout << std::endl;
        
        for (int i = 0; i < BOARD_SIZE; ++i) {
            std::cout << std::setw(2) << i << " ";
            for (int j = 0; j < BOARD_SIZE; ++j) {
                std::cout << board[i][j] << "  ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    
    bool makeMove(int row, int col) {
        if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
            return false;
        }
        if (board[row][col] != '.') {
            return false;
        }
        
        board[row][col] = currentPlayer;
        return true;
    }
    
    bool checkWin(int row, int col) {
        // 检查四个方向：水平、垂直、对角线
        int directions[4][2] = {{0,1}, {1,0}, {1,1}, {1,-1}};
        
        for (int d = 0; d < 4; ++d) {
            int count = 1;
            int dx = directions[d][0], dy = directions[d][1];
            
            // 正方向
            for (int i = 1; i < 5; ++i) {
                int newRow = row + i * dx;
                int newCol = col + i * dy;
                if (newRow >= 0 && newRow < BOARD_SIZE && 
                    newCol >= 0 && newCol < BOARD_SIZE &&
                    board[newRow][newCol] == currentPlayer) {
                    count++;
                } else {
                    break;
                }
            }
            
            // 负方向
            for (int i = 1; i < 5; ++i) {
                int newRow = row - i * dx;
                int newCol = col - i * dy;
                if (newRow >= 0 && newRow < BOARD_SIZE && 
                    newCol >= 0 && newCol < BOARD_SIZE &&
                    board[newRow][newCol] == currentPlayer) {
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
    
    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
    
    char getCurrentPlayer() const {
        return currentPlayer;
    }
    
    void play() {
        std::cout << "🎮 欢迎来到简化版五子棋游戏！" << std::endl;
        std::cout << "X 先手，O 后手" << std::endl;
        std::cout << "输入格式：行 列 (例如: 7 7)" << std::endl;
        std::cout << "输入 -1 -1 退出游戏" << std::endl << std::endl;
        
        while (true) {
            printBoard();
            std::cout << "轮到玩家 " << currentPlayer << " 下棋，请输入坐标: ";
            
            int row, col;
            std::cin >> row >> col;
            
            if (row == -1 && col == -1) {
                std::cout << "游戏结束！" << std::endl;
                break;
            }
            
            if (!makeMove(row, col)) {
                std::cout << "❌ 无效的移动，请重新输入！" << std::endl;
                continue;
            }
            
            if (checkWin(row, col)) {
                printBoard();
                std::cout << "🎉 恭喜玩家 " << currentPlayer << " 获胜！" << std::endl;
                break;
            }
            
            switchPlayer();
        }
    }
};

int main() {
    SimpleGobang game;
    game.play();
    return 0;
} 