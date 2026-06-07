#ifndef MAZE_MAZE_H_
#define MAZE_MAZE_H_

#include <ostream>
#include <vector>

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
  Maze() = default;
  explicit Maze(int rows, int cols);

  int GetRows() const { return rows_; };
  int GetCols() const { return cols_; };
  bool IsConnected(const Cell& cell_a, const Cell& cell_b) const;
  friend std::ostream& operator<<(std::ostream& os, const Maze& maze);

 private:
  int rows_ = 0;
  int cols_ = 0;
  maze::internal::Graph graph_;

  friend class Prim;
  friend class Kruskal;
};

}  // namespace maze

#endif
