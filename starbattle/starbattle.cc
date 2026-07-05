#include "starbattle.h"

#include "renderer.h"

namespace starbattle {

const internal::BoardData& Board::GetBoardData(
    const maze::grid::Cell& cell) const {
  return data_[maze::grid::ToFlatIdx(cell, GetN())];
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
  return renderer::Render(os, board);
}

}  // namespace starbattle
