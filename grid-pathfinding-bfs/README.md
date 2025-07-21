📁 Project : BFS Shortest Path in a Grid
📌 Description
This program finds the shortest path in a 5x5 grid using Breadth-First Search (BFS). The grid has obstacles represented by 1, and the algorithm finds a path from the start point to the goal point avoiding them.

✅ Features
Fixed-size 5x5 grid

Obstacles blocking certain paths

BFS pathfinding logic

Output includes:

Original grid

Grid with the path displayed using *

Coordinate path from start to goal

▶️ How to Run
bash
Copy
Edit
g++ bfs_grid_path.cpp -o bfs_grid_path
./bfs_grid_path
📌 Sample Output
shell
Copy
Edit
Original Grid (# = obstacle):
. . . . .
# # # # .
# . . . .
# # . # .
# . . . .

Path found using BFS! (* = path):
* * * * .
# # # # *
# . . . *
# # . # *
# . . . *

Path coordinates (from start to goal):
(0,0) -> (0,1) -> (0,2) -> ... -> (4,4)
