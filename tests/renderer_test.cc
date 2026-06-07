#include "maze/renderer.h"

#include <sstream>

#include "gtest/gtest.h"

TEST(RenderTest, CorrectlyRender2x3Grid) {
  maze::Maze my_maze(2, 3);
  const std::string expected =
      "+───+───+───+\n"
      "│   │   │   │\n"
      "+───+───+───+\n"
      "│   │   │   │\n"
      "+───+───+───+\n";
  std::ostringstream oss;

  maze::renderer::Render(oss, my_maze);

  EXPECT_EQ(oss.str(), expected);
}
