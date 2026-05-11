#include "maze/maze.h"

#include <algorithm>

bool maze::Maze::IsConnected(const Cell& cell_a, const Cell& cell_b) const {
  if (internal::OutOfBounds(cell_a, GetRows(), GetCols()) ||
      internal::OutOfBounds(cell_b, GetRows(), GetCols())) {
    return false;
  }

  const int cell_a_idx = internal::ToFlatIdx(cell_a, GetCols());
  const int cell_b_idx = internal::ToFlatIdx(cell_b, GetCols());

  return std::ranges::find_if(graph_[cell_a_idx],
                              [cell_b_idx](const auto& edge) {
                                return std::get<0>(edge) == cell_b_idx;
                              }) != std::ranges::end(graph_[cell_a_idx]);
}

int maze::internal::ToFlatIdx(const Cell& cell, int total_cols) {
  const auto& [row, col] = cell;
  return row * total_cols + col;
}

bool maze::internal::OutOfBounds(const Cell& cell, int total_rows,
                                 int total_cols) {
  const auto& [row, col] = cell;
  return row < 0 || row >= total_rows || col < 0 || col >= total_cols;
}
