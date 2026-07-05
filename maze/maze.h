#ifndef MAZE_MAZE_H_
#define MAZE_MAZE_H_

#include <array>
#include <concepts>
#include <ostream>
#include <vector>

namespace maze {

namespace grid {

inline constexpr auto kDirections =
    std::to_array<std::tuple<int, int>>({{0, 1}, {1, 0}});

using Cell = std::tuple<int, int>;

template <typename T>
concept GraphEdge = requires(T t) {
  { t.v } -> std::convertible_to<int>;
};

template <GraphEdge Edge>
using Graph = std::vector<std::vector<Edge>>;

int ToFlatIdx(const Cell& cell, int total_cols);
bool OutOfBounds(const Cell& cell, int total_rows, int total_cols);

template <GraphEdge Edge>
grid::Graph<Edge> ConstructGraph(int rows, int cols) {
  Graph<Edge> graph(rows * cols);

  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      const Cell cell_a = {row, col};
      int curr_idx = ToFlatIdx(cell_a, cols);

      for (const auto [row_delta, col_delta] : kDirections) {
        const Cell cell_b = {row + row_delta, col + col_delta};

        if (OutOfBounds(cell_b, rows, cols)) continue;

        int next_idx = ToFlatIdx(cell_b, cols);
        graph[curr_idx].emplace_back(Edge{.v = next_idx});
        graph[next_idx].emplace_back(Edge{.v = curr_idx});
      }
    }
  }

  return graph;
}

}  // namespace grid

namespace internal {

struct MazeEdge {
  int v;
  float cost;
};
static_assert(maze::grid::GraphEdge<MazeEdge>);

}  // namespace internal

// Holds the maze represented as a graph
class Maze {
 public:
  Maze() = default;
  explicit Maze(int rows, int cols);

  int GetRows() const { return rows_; };
  int GetCols() const { return cols_; };
  bool IsConnected(const grid::Cell& cell_a, const grid::Cell& cell_b) const;
  friend std::ostream& operator<<(std::ostream& os, const Maze& maze);

 private:
  int rows_ = 0;
  int cols_ = 0;
  grid::Graph<internal::MazeEdge> graph_;

  friend class Prim;
  friend class Kruskal;
};

}  // namespace maze

#endif
