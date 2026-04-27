#ifndef LIB_MAZE_H_
#define LIB_MAZE_H_

#include <vector>

namespace maze {

struct Pos {
  int X;
  int Y;
};

// Holds the maze represented as a graph
class Maze {
 public:
  Maze(int rows, int cols) : rows_(rows), cols_(cols) {};

  int GetRows() const { return rows_; };
  int GetCols() const { return cols_; };
  bool IsConnected(Pos L, Pos R) const;

 private:
  using MazeGraph_ = std::vector<std::vector<int>>;
  int rows_;
  int cols_;
  MazeGraph_ graph_;
};

}  // namespace maze

#endif
