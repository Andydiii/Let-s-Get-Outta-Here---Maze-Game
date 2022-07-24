// SEASHELL_READONLY

// Represents a maze
struct maze;

// maze_read() reads and stores a maze descripton from the console. In the maze 
//   description, the following tiles are possible:
//     * walls: X
//     * paths: Space
//     * start: S
//     * exit:  E
//   The outer layer of the maze must be made of either wall or exit tiles. A
//   maze must have exactly one start tile and at LEAST one exit (it can have
//   more than one exit).
// effects: reads from the console
//          allocates memory, client must call maze_destroy
// time:    O(n) [amortized], where n is the area of the maze
struct maze *maze_read(void);

// maze_destroy(maze) frees all resources used by maze.
// effects: *maze becomes invalid
// time:    O(1)
void maze_destroy(struct maze *maze);

// maze_solve(maze) prints out the solution for the maze. In the solution
//   description, the following instructions are valid:
//     * going up: U
//     * going down: D
//     * going left: L
//     * going right: R
//   All directions are relative to the maze: for example, U is always going up,
//   independently from the previous instruction.
// effects: writes to the console
// time:    ???
void maze_solve(struct maze *maze);
