#include "maze.h"
#include "cs136-trace.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct maze {
  char *maze;
  int width;
  int height;
  int len;
  int maxlen;
  int direction;
  // direction % 4 == 0 => North
  // direction % 4 == 1 || -3 => East
  // direction % 4 == 2 || -2 => South
  // direction % 4 == 3 || -1 => West
  int curr_pos;
};

// See maze.h for documentation.
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
struct maze *maze_read(void) {
  struct maze *new_maze = malloc(sizeof(struct maze));
  
  new_maze->maxlen = 1;
  new_maze->maze = malloc(new_maze->maxlen * sizeof(char));
  new_maze->height = 0;
  new_maze->width = 0;
  new_maze->len = 0;
  new_maze->direction = 0;

  char input = ' ';
  int temp_width = 0;
  while (scanf("%c", &input) == 1) {
    if (new_maze->len == new_maze->maxlen) {
      new_maze->maxlen *= 2;
      new_maze->maze = realloc(new_maze->maze, 
                new_maze->maxlen * sizeof(char));
    }
    if (input == '\n') {
       ++new_maze->height;
      if (new_maze->height == 1) {
        new_maze->width = temp_width;
      }
    }

    else if (input == 'S' || input == 'E') {
      if (input == 'S') {
        new_maze->maze[new_maze->len] = input;
      }
      else {
        new_maze->maze[new_maze->len] = input;
      }
      ++new_maze->len;
      ++temp_width;
    }

    else {
      new_maze->maze[new_maze->len] = input;
      ++new_maze->len;
      ++temp_width;
    }
  }
  return new_maze;
}

// See maze.h for documentation.
void maze_destroy(struct maze *maze) {
  assert(maze);
  free(maze->maze);
  free(maze);
}

// See maze.h for documentation.
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
void maze_solve(struct maze *maze) {
  assert(maze);
  int curr_pos = 0;
  //find index of start;
  for (int i = 0; i < maze->len; ++i) {
    if (maze->maze[i] == 'S') {
      curr_pos = i;
      break;
    }
  }
  while (1) {
    if (maze->maze[curr_pos] == 'E') {
      printf("\n");
      return;  
    }
    // when robot is facing north
    else if (maze->direction % 4 == 0) {
      if (maze->maze[curr_pos + 1] != 'X') {
        // if right is not wall;
        printf("R");
        // turn right
        // swap;
        // change pos of S;
        curr_pos = curr_pos + 1;
        ++maze->direction;
      }
      else if (maze->maze[curr_pos - maze->width] != 'X') {
        // if up is not wall;
        // no turn
        // swap;
        // change position of S
        printf("U");
        curr_pos = curr_pos - maze->width;
      }
      else if (maze->maze[curr_pos - 1] != 'X') {
        // if the left hand is not wall
        // change direction
        // swap
        // change pos of S
        printf("L");
        curr_pos = curr_pos - 1;
        --maze->direction;
      }
      else if (maze->maze[curr_pos + maze->width] != 'X') {
        // if back is not wall
        printf("D");
        curr_pos = curr_pos + maze->width;
        maze->direction += 2;
      }
    }
    // the robot is facing east
    else if (maze->direction % 4 == 1 
             || maze->direction % 4 == -3) { 
      // if right is not wall
      if (maze->maze[curr_pos + maze->width] != 'X') {
        printf("D");
        curr_pos = curr_pos + maze->width;
        maze->direction += 1;
      }
      // if straight is not wall
      else if (maze->maze[curr_pos + 1] != 'X') {
        printf("R");
        ++curr_pos;
      }
      // if left is not wall
      else if (maze->maze[curr_pos - maze->width] != 'X') {
        printf("U");
        curr_pos -= maze->width;
        maze->direction -= 1; 
      }
      // if back is not wall
      else if (maze->maze[curr_pos - 1] != 'X') {
        printf("L");
        --curr_pos;
        maze->direction += 2; 
      }
    }
    // if fobot is facing south;
    else if (maze->direction % 4 == 2 || 
             maze->direction % 4 == -2) {
      if (maze->maze[curr_pos - 1] != 'X') {
        printf("L");
        --curr_pos;
        ++maze->direction;
      }
      else if (maze->maze[curr_pos + maze->width] != 'X') {
        printf("D");
        curr_pos += maze->width;
      }
      else if (maze->maze[curr_pos + 1] != 'X') {
        printf("R");
        curr_pos += 1;
        --maze->direction;
      }
      else if (maze->maze[curr_pos - maze->width] != 'X') {
        printf("U");
        curr_pos -= maze->width;
        maze->direction -= 2;
      }
    }
    // when the robot is facing west;
    else if (maze->direction % 4 == 3 || 
             maze->direction % 4 == -1) {
      if (maze->maze[curr_pos - maze->width] != 'X') {
        printf("U");
        curr_pos -= maze->width;
        ++maze->direction;
      }
      else if (maze->maze[curr_pos - 1] != 'X') {
        printf("L");
        curr_pos -= 1;
      }
      else if (maze->maze[curr_pos + maze->width] != 'X') {
        printf("D");
        curr_pos += maze->width;
        --maze->direction;
      }
      else if (maze->maze[curr_pos + 1] != 'X') {
        printf("R");
        curr_pos += 1;
        maze->direction -= 2;
      }
    }
  }
}