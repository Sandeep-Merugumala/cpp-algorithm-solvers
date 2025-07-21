#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

// Define the 3x3 puzzle grid size
const int SIZE = 3;

// Structure to represent a puzzle state
struct State {
    vector<vector<int>> board;
    int blankX, blankY; // Position of the blank tile (0)
    string path;        // Moves taken to reach this state (U, D, L, R)

    State(vector<vector<int>> b, int x, int y, string p = "")
        : board(b), blankX(x), blankY(y), path(p) {}

    // Convert state to string for hashing (used in visited set)
    string toString() const {
        string s;
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                s += to_string(board[i][j]);
        return s;
    }

    bool operator==(const State& other) const {
        return board == other.board;
    }
};

// Check if two states are equal (for goal comparison)
bool isGoal(const State& current, const State& goal) {
    return current.board == goal.board;
}

// Check if a move is valid
bool isValid(int x, int y) {
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
}

// Depth-limited DFS for IDDFS
bool depthLimitedSearch(State current, const State& goal, int depth,
                        unordered_set<string>& visited, string& solution) {
    if (depth < 0) return false;
    if (isGoal(current, goal)) {
        solution = current.path;
        return true;
    }

    // Possible moves: up, down, left, right
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    char moves[4] = {'U', 'D', 'L', 'R'};

    for (int i = 0; i < 4; i++) {
        int newX = current.blankX + dx[i];
        int newY = current.blankY + dy[i];

        if (isValid(newX, newY)) {
           
            vector<vector<int>> newBoard = current.board;
            swap(newBoard[current.blankX][current.blankY], newBoard[newX][newY]);
            State next(newBoard, newX, newY, current.path + moves[i]);

            string stateStr = next.toString();
            if (visited.find(stateStr) == visited.end()) {
                visited.insert(stateStr);
                if (depthLimitedSearch(next, goal, depth - 1, visited, solution))
                    return true;
            }
        }
    }
    return false;
}

// Function to check if puzzle is solvable
bool isSolvable(const vector<vector<int>>& board) {
    // Convert 2D board to 1D array (excluding the blank tile)
    vector<int> flatBoard;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != 0) {
                flatBoard.push_back(board[i][j]);
            }
        }
    }
    
    // Count inversions
    int inversions = 0;
    for (int i = 0; i < flatBoard.size(); i++) {
        for (int j = i + 1; j < flatBoard.size(); j++) {
            if (flatBoard[i] > flatBoard[j]) {
                inversions++;
            }
        }
    }
    
    // Find blank row position from bottom (0-indexed)
    int blankRow = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                blankRow = SIZE - 1 - i;
                break;
            }
        }
    }
    
    // If grid width is odd, puzzle is solvable if inversions count is even
    // If grid width is even:
    //   - If blank is on an even row from bottom, inversions must be odd
    //   - If blank is on an odd row from bottom, inversions must be even
    if (SIZE % 2 == 1) {
        return inversions % 2 == 0;
    } else {
        return (blankRow % 2 == 0) ? (inversions % 2 == 1) : (inversions % 2 == 0);
    }
}

// IDDFS to solve the 8-puzzle
bool solve8Puzzle(State start, State goal, string& solution) {
    // Check if puzzle is solvable before attempting to solve
    if (!isSolvable(start.board)) {
        return false;
    }
    
    // Max depth is bounded by the number of possible moves (heuristic: ~31 for 8-puzzle)
    for (int depth = 0; depth <= 31; depth++) {
        cout << "Searching at depth " << depth << "..." << endl;
        unordered_set<string> visited;
        visited.insert(start.toString());
        if (depthLimitedSearch(start, goal, depth, visited, solution)) {
            cout << "Solution found at depth: " << depth << endl;
            return true;
        }
    }
    return false;
}

void printState(const vector<vector<int>>& board) {
    cout << "+-------+" << endl;
    for (int i = 0; i < SIZE; i++) {
        cout << "| ";
        for (int j = 0; j < SIZE; j++) {
            cout << (board[i][j] == 0 ? " " : to_string(board[i][j])) << " ";
        }
        cout << "|" << endl;
    }
    cout << "+-------+" << endl;
}

// Function to display solution path
void displaySolution(const vector<vector<int>>& initialBoard, const string& solution) {
    vector<vector<int>> board = initialBoard;
    int blankX = 0, blankY = 0;
    
    // Find initial blank position
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                blankX = i;
                blankY = j;
                break;
            }
        }
    }
    
    cout << "Solution steps:" << endl;
    cout << "Initial State:" << endl;
    printState(board);
    
    // Possible moves: up, down, left, right
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    string moveNames[4] = {"Up", "Down", "Left", "Right"};
    
    for (char move : solution) {
        int moveIdx;
        switch (move) {
            case 'U': moveIdx = 0; break;
            case 'D': moveIdx = 1; break;
            case 'L': moveIdx = 2; break;
            case 'R': moveIdx = 3; break;
            default: continue;
        }
        
        int newX = blankX + dx[moveIdx];
        int newY = blankY + dy[moveIdx];
        
        // Make the move
        swap(board[blankX][blankY], board[newX][newY]);
        blankX = newX;
        blankY = newY;
        
        cout << "Move: " << moveNames[moveIdx] << endl;
        printState(board);
    }
}

// Extract all numbers from a board into a vector for comparison
vector<int> extractNumbers(const vector<vector<int>>& board) {
    vector<int> numbers;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            numbers.push_back(board[i][j]);
        }
    }
    sort(numbers.begin(), numbers.end());
    return numbers;
}

// Validate that boards have same set of numbers
bool validateBoards(const vector<vector<int>>& initial, const vector<vector<int>>& goal) {
    vector<int> initialNums = extractNumbers(initial);
    vector<int> goalNums = extractNumbers(goal);
    
    if (initialNums != goalNums) {
        ostringstream oss;
        oss << "Initial and goal boards must contain the same set of numbers. ";
        oss << "Initial: ";
        for (int num : initialNums) {
            oss << num << " ";
        }
        oss << "Goal: ";
        for (int num : goalNums) {
            oss << num << " ";
        }
        throw runtime_error(oss.str());
    }
    
    // Validate numbers are in proper range for 8-puzzle (0-8)
    if (initialNums[0] != 0 || initialNums[SIZE*SIZE-1] > 8) {
        throw runtime_error("For 8-puzzle, numbers should be in range 0-8");
    }
    
    return true;
}

int main() {
    try {
        vector<vector<int>> initialBoard = {
            {1, 3, 6},
            {4, 2, 0},  
            {7, 5, 8}
        };

        vector<vector<int>> goalBoard = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 0}
        };

        // Validate board dimensions
        if (initialBoard.size() != SIZE || goalBoard.size() != SIZE) {
            throw runtime_error("Board dimensions must be " + to_string(SIZE) + "x" + to_string(SIZE));
        }
        for (int i = 0; i < SIZE; i++) {
            if (initialBoard[i].size() != SIZE || goalBoard[i].size() != SIZE) {
                throw runtime_error("Board dimensions must be " + to_string(SIZE) + "x" + to_string(SIZE));
            }
        }

        // Validate that both boards have the same set of numbers
        validateBoards(initialBoard, goalBoard);

        // Find blank position in initial state
        int blankX = -1, blankY = -1;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (initialBoard[i][j] == 0) {
                    blankX = i;
                    blankY = j;
                }
            }
        }
        
        // Find blank position in goal state
        int goalBlankX = -1, goalBlankY = -1;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (goalBoard[i][j] == 0) {
                    goalBlankX = i;
                    goalBlankY = j;
                }
            }
        }
        
        if (blankX == -1 || blankY == -1) {
            throw runtime_error("Initial board must contain a blank tile (0)");
        }
        if (goalBlankX == -1 || goalBlankY == -1) {
            throw runtime_error("Goal board must contain a blank tile (0)");
        }

        State start(initialBoard, blankX, blankY);
        State goal(goalBoard, goalBlankX, goalBlankY); // Dynamic blank position in goal

        cout << "Initial State:" << endl;
        printState(initialBoard);

        cout << "Goal State:" << endl;
        printState(goalBoard);

        // Check solvability
        if (!isSolvable(initialBoard)) {
            cout << "This puzzle configuration is not solvable!" << endl;
            return 0;
        }

        string solution;
        if (solve8Puzzle(start, goal, solution)) {
            cout << "Solution found! Moves: " << solution << endl;
            cout << "Number of moves: " << solution.length() << endl;
            
            // Display solution path
            displaySolution(initialBoard, solution);
        } else {
            cout << "No solution exists!" << endl;
        }

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
