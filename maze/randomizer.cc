#include "randomizer.h"

#include <array>
#include <functional>
#include <iterator>
#include <queue>
#include <unordered_set>
#include <vector>

#include "maze.h"

namespace {

constexpr auto kDirections =
    std::to_array<std::tuple<int, int>>({{0, 1}, {1, 0}});

// weight, u, v
using MinHeapEdge = std::tuple<float, int, int>;
using MinHeap = std::priority_queue<MinHeapEdge, std::vector<MinHeapEdge>,
                                    std::greater<MinHeapEdge>>;

}  // namespace

maze::Maze::Graph maze::Prim::ConstructGraph(int rows, int cols) {
  Maze::Graph graph(rows * cols);

  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      const Cell cell_a = {row, col};
      int curr_idx = internal::ToFlatIdx(cell_a, cols);

      for (const auto [row_delta, col_delta] : kDirections) {
        const Cell cell_b = {row + row_delta, col + col_delta};

        if (internal::OutOfBounds(cell_b, rows, cols)) continue;

        int next_idx = internal::ToFlatIdx(cell_b, cols);

        graph[curr_idx].emplace_back(next_idx, 0.0f);
        graph[next_idx].emplace_back(curr_idx, 0.0f);
      }
    }
  }

  return graph;
}

maze::Maze::Graph maze::Prim::ConstructMST(const Maze::Graph& graph) {
  const int total_size = graph.size();
  CHECK(total_size > 0);

  Maze::Graph mst(total_size);
  MinHeap heap;
  const int start_cell = 0;
  std::unordered_set<int> seen_cells = {start_cell};

  for (const auto [next_cell, weight] : graph[start_cell]) {
    heap.emplace(weight, start_cell, next_cell);
  }

  while (std::ssize(seen_cells) < total_size && heap.size() > 0) {
    const auto [cost, from_cell, current_cell] = heap.top();
    heap.pop();

    if (seen_cells.contains(current_cell)) continue;

    seen_cells.insert(current_cell);

    mst[current_cell].emplace_back(from_cell, cost);
    mst[from_cell].emplace_back(current_cell, cost);

    for (const auto [next_cell, weight] : graph[current_cell]) {
      if (seen_cells.contains(next_cell)) continue;

      heap.emplace(weight, current_cell, next_cell);
    }
  }

  CHECK(std::ssize(seen_cells) == total_size);

  return mst;
}
