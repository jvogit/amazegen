#include "randomizer.h"

#include <algorithm>
#include <array>
#include <functional>
#include <iterator>
#include <numeric>
#include <queue>
#include <unordered_set>
#include <vector>

#include "absl/container/flat_hash_set.h"
#include "absl/log/check.h"
#include "maze.h"

namespace {

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

grid::Graph<internal::MazeEdge> Prim::ConstructMST(
    const grid::Graph<internal::MazeEdge>& graph) {
  const int total_size = graph.size();
  CHECK(total_size > 0);

  grid::Graph<internal::MazeEdge> mst(total_size);
  MinHeap heap;
  const int start_cell = 0;
  absl::flat_hash_set<int> seen_cells = {start_cell};

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

grid::Graph<internal::MazeEdge> Kruskal::ConstructMST(
    const grid::Graph<internal::MazeEdge>& graph) {
  // sort edges by weight
  // connectvity set
  // while edges
  //   get edge, if both are in DSU, continue
  //   add edge to tree, mark both ends as seen
  const int total_size = graph.size();
  CHECK(total_size > 0);
  grid::Graph<internal::MazeEdge> mst(total_size);
  std::vector<GraphEdge> edges;
  // 2 * kDirections.size() since kDirection only right and down moves. Each
  // cell has 4 possible edges.
  edges.reserve(2 * grid::kDirections.size() * total_size);

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
