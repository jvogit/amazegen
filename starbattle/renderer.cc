#include "renderer.h"

#include <string>

#include "absl/strings/str_cat.h"

namespace renderer {

std::ostream& Render(std::ostream& os, const starbattle::Board& board) {
  CHECK(board.GetN() > 0);

  os << "+";

  for (int col = 0; col < board.GetN(); ++col) os << "───+";

  os << "\n";

  for (int row = 0; row < board.GetN(); ++row) {
    std::string middle = "│";
    std::string bottom = "+";
    for (int col = 0; col < board.GetN(); ++col) {
      const auto board_data = board.GetBoardData({row, col});
      CHECK_GE(board_data.color, 0);
      char c = board_data.color == -1 ? ' ' : '0' + board_data.color;
      middle += absl::StrCat(" ", std::string(1, c), " │");
      bottom += "───+";
    }
    os << middle << "\n" << bottom << "\n";
  }

  return os;
}

}  // namespace renderer
