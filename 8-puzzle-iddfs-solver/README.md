📁 Project : 8-Puzzle Solver using IDDFS
📌 Description
This project implements a solver for the classic 8-puzzle problem using Iterative Deepening Depth-First Search (IDDFS). It takes an initial and a goal configuration of a 3x3 puzzle and finds a sequence of moves to solve it.

✅ Features
Validates puzzle solvability

Implements IDDFS (combines DFS and iterative deepening)

Tracks and displays each move (Up, Down, Left, Right)

Pretty prints puzzle states after each move

▶️ How to Run
bash
Copy
Edit
g++ iddfs_8puzzle.cpp -o iddfs_8puzzle
./iddfs_8puzzle
📌 Sample Output
sql
Copy
Edit
Initial State:
+-------+
| 1 3 6 |
| 4 2   |
| 7 5 8 |
+-------+

Goal State:
+-------+
| 1 2 3 |
| 4 5 6 |
| 7 8   |
+-------+

Solution found! Moves: DLURD...
Number of moves: 13

Solution steps:
Initial State:
...
Move: Down
+-------+
| 1 3   |
| 4 2 6 |
| 7 5 8 |
+-------+
...
🧩 Requirements
C++11 or higher

Standard C++ compiler like g++

🧠 Concepts Used
BFS (Breadth-First Search)

DFS (Depth-First Search)

IDDFS (Iterative Deepening DFS)

Puzzle Solvability Check

Grid Navigation

📜 License
MIT License (You may freely use, modify, and distribute this code)
