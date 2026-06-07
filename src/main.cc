#include <iostream>
#include <random>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/log.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "maze/randomizer.h"

ABSL_FLAG(int, rows, 2, "Number of rows for maze");
ABSL_FLAG(int, cols, 2, "Number of cols for maze");
ABSL_FLAG(std::string, algo, "prim",
          "MST Algorithm to use: prim (default), kruskal");

namespace {

template <std::uniform_random_bit_generator G>
absl::StatusOr<maze::Maze> GetMaze(G& gen) {
  const auto algo = absl::GetFlag(FLAGS_algo);
  const auto rows = absl::GetFlag(FLAGS_rows);
  const auto cols = absl::GetFlag(FLAGS_cols);

  if (algo == "prim") {
    return maze::Prim::RandomizeMaze(rows, cols, gen);
  } else if (algo == "kruskal") {
    return maze::Kruskal::RandomizeMaze(rows, cols, gen);
  }

  return absl::InvalidArgumentError(absl::StrCat("unknown algorithm: ", algo));
}

}  // namespace

int main(int argc, char* argv[]) {
  absl::ParseCommandLine(argc, argv);

  std::random_device rd;
  std::mt19937 testgen(rd());
  auto maze = GetMaze(testgen);
  if (!maze.ok()) {
    LOG(FATAL) << maze.status();
  }

  LOG(INFO) << "Rows: " << maze->GetRows() << " Cols: " << maze->GetCols()
            << "\n";

  LOG(INFO) << "\n" << maze << std::endl;

  return 0;
}
