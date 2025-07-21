# cpp-algorithm-solvers
# C++ Algorithm Solvers

This monorepo contains a collection of classic C++ implementations of popular algorithm-based solvers:

## 📁 Projects

### 1. [Grid Pathfinding using BFS](grid-pathfinding-bfs/)
A 5x5 grid navigation solver using Breadth-First Search (BFS) to find the shortest path from start to goal avoiding obstacles.

### 2. [8 Puzzle Solver using IDDFS](8-puzzle-iddfs-solver/)
Solves the 8-puzzle problem using Iterative Deepening Depth-First Search (IDDFS) with puzzle solvability validation and step-wise move tracking.

### 3. [4x4 Sudoku Solver using Backtracking](4x4-sudoku-solver/)
Backtracking-based solver for 4x4 Sudoku puzzles, including input validation and structured output.

---

## 🧠 Algorithms Covered

- Breadth-First Search (BFS)
- Iterative Deepening Depth-First Search (IDDFS)
- Backtracking
- Grid Traversal
- Puzzle Solvability Check

---

## 🛠️ Requirements

- C++11 or later
- g++ or any compatible C++ compiler

## ▶️ Running the Projects

Each project has its own folder with:
- Source file
- Dedicated README for instructions and sample output

Example:
```bash
cd grid-pathfinding-bfs
g++ bfs_grid_path.cpp -o bfs_grid_path
./bfs_grid_path
