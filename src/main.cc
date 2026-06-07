#include <iostream>
#include <random>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "maze/randomizer.h"
#include "maze/renderer.h"

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

  maze::renderer::Render(std::cout, my_maze);

  std::cout << std::endl;

  return 0;
}
