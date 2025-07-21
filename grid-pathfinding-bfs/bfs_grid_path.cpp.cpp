#include <iostream>
#include <vector>
#include <queue>
#include <algorithm> // Added for reverse()

using namespace std;

const int ROWS = 5;
const int COLS = 5;

struct Point {
    int x, y;
    Point(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
};

bool isValid(int x, int y, vector<vector<int>>& grid) {
    return (x >= 0 && x < ROWS && y >= 0 && y < COLS && grid[x][y] != 1);
}

// BFS-based shortest path search
bool findPath(vector<vector<int>>& grid, Point start, Point goal, vector<Point>& path) {
    if (grid[start.x][start.y] == 1 || grid[goal.x][goal.y] == 1) {
        return false; // Start or goal is an obstacle
    }

    if (start.x == goal.x && start.y == goal.y) {
        path.push_back(start); // Start is the goal, return itself as the path
        return true;
    }

    int dx[4] = {-1, 0, 1, 0}; // up, right, down, left
    int dy[4] = {0, 1, 0, -1};

    vector<vector<bool>> visited(ROWS, vector<bool>(COLS, false));
    vector<vector<Point>> parent(ROWS, vector<Point>(COLS, Point(-1, -1)));

    queue<Point> q;
    q.push(start);
    visited[start.x][start.y] = true;

    while (!q.empty()) {
        Point current = q.front();
        q.pop();

        if (current.x == goal.x && current.y == goal.y) {
            // Reconstruct path from goal to start
            path.clear();
            Point p = current;
            while (p.x != -1 && p.y != -1) {
                path.push_back(p);
                p = parent[p.x][p.y];
            }
            reverse(path.begin(), path.end()); // ✅ Corrected with #include <algorithm>
            return true;
        }

        for (int i = 0; i < 4; i++) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            if (isValid(newX, newY, grid) && !visited[newX][newY]) {
                q.push(Point(newX, newY));
                visited[newX][newY] = true;
                parent[newX][newY] = current;
            }
        }
    }
    return false; // No path found
}

void printGrid(vector<vector<int>>& grid, const vector<Point>& path) {
    vector<vector<char>> display(ROWS, vector<char>(COLS, '.'));

    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            if (grid[i][j] == 1)
                display[i][j] = '#';

    for (Point p : path)
        display[p.x][p.y] = '*';

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++)
            cout << display[i][j] << " ";
        cout << endl;
    }
}

int main() {
    vector<vector<int>> grid = {
        {0, 0, 0, 0, 0},
        {1, 1, 1, 1, 0},
        {1, 0, 0, 0, 0},
        {1, 1, 0, 1, 0},
        {1, 0, 0, 0, 0} // Final destination
    };

    Point start(0, 0);
    Point goal(4, 4);
    vector<Point> path;

    if (grid[start.x][start.y] == 1 || grid[goal.x][goal.y] == 1) {
        cout << "Error: Start or goal is inside an obstacle!" << endl;
        return 0;
    }
    if (start.x < 0 || start.y < 0 || start.x >= ROWS || start.y >= COLS ||
    goal.x < 0 || goal.y < 0 || goal.x >= ROWS || goal.y >= COLS) {
    cout << "Error: Start or goal is out of grid bounds!" << endl;
    return 0;
}


    cout << "Original Grid (# = obstacle):" << endl;
    printGrid(grid, vector<Point>());

    if (findPath(grid, start, goal, path)) {
        cout << "\nPath found using BFS! (* = path):" << endl;
        printGrid(grid, path);

        cout << "\nPath coordinates (from start to goal):" << endl;
        for (size_t i = 0; i < path.size(); i++)
            cout << "(" << path[i].x << "," << path[i].y << ")" << (i < path.size() - 1 ? " -> " : "\n");
    } else {
        cout << "\nNo path found!" << endl;
    }

    return 0;
}
