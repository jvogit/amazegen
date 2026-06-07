#include "renderer.h"

#include "absl/log/check.h"

namespace maze::renderer {

std::ostream& Render(std::ostream& os, const Maze& maze) {
  CHECK(maze.GetRows() > 0);
  CHECK(maze.GetCols() > 0);

  os << "+";

  for (int col = 0; col < maze.GetCols(); ++col) os << "───+";

  os << "\n";

  for (int row = 0; row < maze.GetRows(); ++row) {
    std::string middle = "│";
    std::string bottom = "+";

    for (int col = 0; col < maze.GetCols(); ++col) {
      Cell cell = {row, col};
      Cell cell_right = {row, col + 1};
      Cell cell_down = {row + 1, col};

      if (internal::OutOfBounds(cell_right, maze.GetRows(), maze.GetCols()) ||
          !maze.IsConnected(cell, cell_right)) {
        middle += "   │";
      } else {
        middle += "    ";
      }

      if (internal::OutOfBounds(cell_down, maze.GetRows(), maze.GetCols()) ||
          !maze.IsConnected(cell, cell_down)) {
        bottom += "───+";
      } else {
        bottom += "   +";
      }
    }

    os << middle << "\n" << bottom << "\n";
  }

  return os;
}

}  // namespace maze::renderer
