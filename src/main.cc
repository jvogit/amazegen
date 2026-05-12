#include <iostream>
#include <random>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/check.h"
#include "maze/randomizer.h"

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

ABSL_FLAG(int, rows, 2, "Number of rows for maze");
ABSL_FLAG(int, cols, 2, "Number of cols for maze");

int main(int argc, char* argv[]) {
  absl::ParseCommandLine(argc, argv);
  std::random_device rd;
  std::mt19937 testgen(rd());
  maze::Maze my_maze = maze::Prim::RandomizeMaze(
      absl::GetFlag(FLAGS_rows), absl::GetFlag(FLAGS_cols), testgen);

  std::cout << "Rows: " << my_maze.GetRows() << " Cols: " << my_maze.GetCols()
            << "\n";

  render(std::cout, my_maze);

  std::cout << std::endl;

  return 0;
}
