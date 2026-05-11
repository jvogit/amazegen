#include "randomizer.h"

#include <array>
#include <random>
#include <vector>

#include "maze.h"

namespace {

constexpr auto kDirections =
    std::to_array<std::tuple<int, int>>({{0, 1}, {1, 0}});

}  // namespace

template <std::uniform_random_bit_generator G>
maze::Maze maze::Prim::Randomize(int rows, int cols, G& gen) {
  maze::Maze maze(rows, cols);

  maze::Maze::Graph graph = ConstructGraph(rows, cols);

  RandomizeEdgeWeights(graph, gen);

  return maze;
};

maze::Maze::Graph maze::Prim::ConstructGraph(int rows, int cols) {
  maze::Maze::Graph graph(rows * cols, std::vector<maze::Maze::Edge>());

  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      const Cell cell_a = {row, col};
      int idx = maze::internal::ToFlatIdx(cell_a, rows);

      for (const auto [row_delta, col_delta] : kDirections) {
        const Cell cell_b = {row + row_delta, col + col_delta};

        if (maze::internal::OutOfBounds(cell_b, rows, cols)) continue;

        int idx_n = maze::internal::ToFlatIdx(cell_b, rows);

        graph[idx].emplace_back(idx_n, 0.0f);
        graph[idx_n].emplace_back(idx, 0.0f);
      }
    }
  }

  return graph;
}

template <std::uniform_random_bit_generator G>
void maze::Prim::RandomizeEdgeWeights(Maze::Graph& graph, G& gen) {
  std::uniform_real_distribution<float> distrib(0.0f, 1.0f);

  for (const auto& edge_list : graph) {
    for (const auto& [to, weight] : edge_list) {
      weight = distrib(gen);
    }
  }
}
