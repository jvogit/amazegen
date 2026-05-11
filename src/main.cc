#include <iostream>

#include "absl/log/check.h"
#include "maze/maze.h"

namespace {
void render(std::ostream& os, maze::Maze& maze) {
  CHECK(maze.GetRows() > 0);
  CHECK(maze.GetCols() > 0);

  os << "+";

  for (int col = 0; col < maze.GetCols(); ++col) os << "───+";

  os << "\n";

  for (int row = 0; row < maze.GetRows(); ++row) {
    std::string middle = "│";
    std::string bottom = "+";

    for (int col = 0; col < maze.GetCols(); ++col) {
      maze::Cell cell = {row, col};
      maze::Cell cell_right = {row, col + 1};
      maze::Cell cell_down = {row + 1, col};

      if (maze::internal::OutOfBounds(cell_right, maze.GetRows(),
                                      maze.GetCols()) ||
          !maze.IsConnected(cell, cell_right)) {
        middle += "   │";
      } else {
        middle += "    ";
      }

      if (maze::internal::OutOfBounds(cell_down, maze.GetRows(),
                                      maze.GetCols()) ||
          !maze.IsConnected(cell, cell_down)) {
        bottom += "───+";
      } else {
        bottom += "   +";
      }
    }

    os << middle << "\n" << bottom << "\n";
  }
}
}  // namespace

int main() {
  maze::Maze my_maze(3, 4);

  std::cout << "Rows: " << my_maze.GetRows() << " Cols: " << my_maze.GetCols()
            << "\n";

  render(std::cout, my_maze);

  std::cout << std::endl;

  return 0;
}
