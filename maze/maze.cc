#include "maze/maze.h"

#include <algorithm>

bool maze::Maze::IsConnected(int cell_a, int cell_b) const {
  return std::ranges::find(graph_[cell_a], cell_b) !=
         std::ranges::end(graph_[cell_a]);
}
