#include "randomizer.h"

#include <algorithm>
#include <array>
#include <functional>
#include <iterator>
#include <numeric>
#include <queue>
#include <unordered_set>
#include <vector>

#include "absl/log/check.h"
#include "maze.h"

namespace {

constexpr auto kDirections =
    std::to_array<std::tuple<int, int>>({{0, 1}, {1, 0}});

// weight, u, v
using GraphEdge = std::tuple<float, int, int>;
using MinHeap = std::priority_queue<GraphEdge, std::vector<GraphEdge>,
                                    std::greater<GraphEdge>>;

class DSU {
 public:
  explicit DSU(int size) : parent_(size), rank_(size, 0) {
    std::iota(parent_.begin(), parent_.end(), 0);
  }

  inline bool Union(int u, int v) {
    auto u_root = Find(u);
    auto v_root = Find(v);

    if (u_root == v_root) {
      return false;
    }

    if (rank_[u_root] > rank_[v_root]) {
      parent_[v_root] = u_root;
    } else if (rank_[v_root] > rank_[u_root]) {
      parent_[u_root] = v_root;
    } else {
      parent_[u_root] = v_root;
      ++rank_[v_root];
    }

    return true;
  }

 private:
  std::vector<int> parent_;
  std::vector<int> rank_;

  inline int Find(int u) {
    if (parent_[u] == u) {
      return u;
    }

    parent_[u] = Find(parent_[u]);

    return parent_[u];
  }
};

}  // namespace

namespace maze {

namespace internal {

Graph ConstructGraph(int rows, int cols) {
  Graph graph(rows * cols);

  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      const Cell cell_a = {row, col};
      int curr_idx = ToFlatIdx(cell_a, cols);

      for (const auto [row_delta, col_delta] : kDirections) {
        const Cell cell_b = {row + row_delta, col + col_delta};

        if (OutOfBounds(cell_b, rows, cols)) continue;

        int next_idx = ToFlatIdx(cell_b, cols);

        graph[curr_idx].emplace_back(next_idx, 0.0f);
        graph[next_idx].emplace_back(curr_idx, 0.0f);
      }
    }
  }

  return graph;
}

}  // namespace internal

internal::Graph Prim::ConstructMST(const internal::Graph& graph) {
  const int total_size = graph.size();
  CHECK(total_size > 0);

  internal::Graph mst(total_size);
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

internal::Graph Kruskal::ConstructMST(const internal::Graph& graph) {
  // sort edges by weight
  // connectvity set
  // while edges
  //   get edge, if both are in DSU, continue
  //   add edge to tree, mark both ends as seen
  const int total_size = graph.size();
  CHECK(total_size > 0);
  internal::Graph mst(total_size);
  std::vector<GraphEdge> edges;
  // 2 * kDirections.size() since kDirection only right and down moves. Each
  // cell has 4 possible edges.
  edges.reserve(2 * kDirections.size() * total_size);

  for (int from = 0; from < total_size; ++from) {
    for (const auto [to, cst] : graph[from]) {
      // monotonically increasing edges only, since it is an undirected graph
      // avoids needless, duplicated edges
      if (to > from) {
        edges.emplace_back(cst, from, to);
      }
    }
  }

  std::ranges::sort(edges);

  // disjoint set union find, to test connectivity
  DSU dsu(total_size);

  for (const auto& [cst, u, v] : edges) {
    if (!dsu.Union(u, v)) {
      continue;
    }

    mst[u].emplace_back(v, cst);
    mst[v].emplace_back(u, cst);
  }

  return mst;
}

}  // namespace maze
