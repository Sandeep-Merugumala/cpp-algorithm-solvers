🧩 Project: 4x4 Sudoku Solver (C++)
📌 Description
This project implements a backtracking algorithm to solve a 4x4 Sudoku puzzle. The puzzle uses digits from 1 to 4, and it must satisfy:

Each digit appears only once per row

Each digit appears only once per column

Each digit appears only once per 2x2 subgrid

The board is represented as a 2D vector, with 0 indicating empty cells.

✅ Features
Supports standard 4x4 Sudoku puzzles

Uses backtracking to recursively solve the puzzle

Prints board before and after solving

Includes board validation to ensure inputs are in range 0-4

Outputs in a readable grid format

📂 File Structure
bash
Copy
Edit
sudoku_solver.cpp   # Main source file
README.md           # This file
▶️ How to Compile and Run
bash
Copy
Edit
g++ sudoku_solver.cpp -o sudoku_solver
./sudoku_solver
📌 Sample Output
sql
Copy
Edit
Initial 4x4 Sudoku Puzzle:
+-----+-----+
| 1 0 | 0 0 |
| 0 0 | 4 0 |
+-----+-----+
| 0 2 | 0 0 |
| 0 0 | 0 3 |
+-----+-----+

Solved 4x4 Sudoku Puzzle:
+-----+-----+
| 1 4 | 3 2 |
| 2 3 | 4 1 |
+-----+-----+
| 3 2 | 1 4 |
| 4 1 | 2 3 |
+-----+-----+
🔍 Algorithm
Backtracking is used to try placing numbers in empty cells.

For each cell, it attempts digits 1 to 4.

Validity is checked across row, column, and 2x2 box.

If a placement leads to a dead end, it backtracks and tries the next number.

🧠 Concepts Used
Backtracking

Constraint Satisfaction

Grid and Matrix Traversal

Input Validation

🧑‍💻 Author
Developed as part of a learning project or algorithm implementation in C++.

📜 License
This project is open-source and free to use under the MIT License.
