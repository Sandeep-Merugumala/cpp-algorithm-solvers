#include <iostream>
#include <vector>
#include <stdexcept>

const int N = 4; // Size of the 4x4 Sudoku board

// Function to validate that the input board contains only valid numbers (0-4)
bool validateBoard(const std::vector<std::vector<int>>& board) {
    if (board.size() != N) {
        return false;
    }
    
    for (int row = 0; row < N; row++) {
        if (board[row].size() != N) {
            return false;
        }
        
        for (int col = 0; col < N; col++) {
            if (board[row][col] < 0 || board[row][col] > N) {
                return false;
            }
        }
    }
    return true;
}

// Function to print the Sudoku board with block separation
void printBoard(const std::vector<std::vector<int>>& board) {
    std::cout << "+-----+-----+" << std::endl;
    for (int row = 0; row < N; row++) {
        std::cout << "| ";
        for (int col = 0; col < N; col++) {
            std::cout << board[row][col] << " ";
            // Add vertical separator after every 2 columns
            if (col == 1) {
                std::cout << "| ";
            }
        }
        std::cout << "|" << std::endl;
        
        // Add horizontal separator after every 2 rows
        if (row == 1) {
            std::cout << "+-----+-----+" << std::endl;
        }
    }
    std::cout << "+-----+-----+" << std::endl << std::endl;
}

// Function to check if placing 'num' at (row, col) is safe
bool isSafe(const std::vector<std::vector<int>>& board, int row, int col, int num) {
    // Check row
    for (int c = 0; c < N; c++) {
        if (board[row][c] == num) {
            return false;
        }
    }

    // Check column
    for (int r = 0; r < N; r++) {
        if (board[r][col] == num) {
            return false;
        }
    }

    // Check 2x2 block
    int startRow = row - row % 2; // Start of the 2x2 block
    int startCol = col - col % 2;
    for (int r = 0; r < 2; r++) {
        for (int c = 0; c < 2; c++) {
            if (board[startRow + r][startCol + c] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to find an empty cell (returns true if found, false if none)
bool findEmpty(const std::vector<std::vector<int>>& board, int& row, int& col) {
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (board[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

// Backtracking function to solve Sudoku
bool solveSudoku(std::vector<std::vector<int>>& board) {
    int row, col;

    // If no empty cell is found, the puzzle is solved
    if (!findEmpty(board, row, col)) {
        return true;
    }

    // Try numbers 1 to 4 in the empty cell
    for (int num = 1; num <= N; num++) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num; // Place the number

            // Recur to solve the rest of the puzzle
            if (solveSudoku(board)) {
                return true;
            }

            // If placing 'num' didn't lead to a solution, backtrack
            board[row][col] = 0;
        }
    }

    return false; // No solution found
}

int main() {
    try {
        // Example 4x4 Sudoku puzzle (0 represents empty cells)
        std::vector<std::vector<int>> board = {
            {1,0,0,0},
            {0,0,4,0},
            {0,2,0,0},
            {0,0,0,3}
        };

        // Validate the board before solving
        if (!validateBoard(board)) {
            throw std::invalid_argument("Invalid Sudoku board: contains numbers outside the range 0-4");
        }

        std::cout << "Initial 4x4 Sudoku Puzzle:" << std::endl;
        printBoard(board);

        if (solveSudoku(board)) {
            std::cout << "Solved 4x4 Sudoku Puzzle:" << std::endl;
            printBoard(board);
        } else {
            std::cout << "No solution exists for this puzzle." << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

