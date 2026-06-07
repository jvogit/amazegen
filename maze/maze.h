#ifndef MAZE_MAZE_H_
#define MAZE_MAZE_H_

#include <iterator>
#include <vector>

#include "absl/log/check.h"

namespace maze {

using Cell = std::tuple<int, int>;

namespace internal {

// to, cost
using Edge = std::tuple<int, float>;
using Graph = std::vector<std::vector<Edge>>;

int ToFlatIdx(const Cell& cell, int total_cols);
bool OutOfBounds(const Cell& cell, int total_rows, int total_cols);

}  // namespace internal

// Holds the maze represented as a graph
class Maze {
 public:
  explicit Maze(int rows, int cols)
      : rows_(rows), cols_(cols), graph_(rows * cols) {
    CHECK_EQ(std::ssize(graph_), rows * cols);
  };

  int GetRows() const { return rows_; };
  int GetCols() const { return cols_; };
  bool IsConnected(const Cell& cell_a, const Cell& cell_b) const;

 private:
  int rows_;
  int cols_;
  maze::internal::Graph graph_;

  friend class Prim;
  friend class Kruskal;
};

}  // namespace maze

#endif
