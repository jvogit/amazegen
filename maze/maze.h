#ifndef MAZE_MAZE_H_
#define MAZE_MAZE_H_

#include <vector>

namespace maze {

// Holds the maze represented as a graph
class Maze {
 public:
  Maze(int rows, int cols) : rows_(rows), cols_(cols), graph_(rows) {};

  int GetRows() const { return rows_; };
  int GetCols() const { return cols_; };
  bool IsConnected(int cell_a, int cell_b) const;

 private:
  using MazeGraph_ = std::vector<std::vector<int>>;
  int rows_;
  int cols_;
  MazeGraph_ graph_;
};

}  // namespace maze

#endif
