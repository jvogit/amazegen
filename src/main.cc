#include <iostream>

#include "maze/maze.h"

int main() {
  maze::Maze my_maze(3, 4);

  std::cout << "Rows: " << my_maze.GetRows() << " Cols: " << my_maze.GetCols()
            << std::endl;

  return 0;
}
