#include "maze/maze.h"

#include "gtest/gtest.h"

TEST(MazeTest, Initialization) {
  int expected_rows = 3;
  int expected_cols = 2;

  maze::Maze my_maze(expected_rows, expected_cols);
  EXPECT_EQ(my_maze.GetRows(), expected_rows);
  EXPECT_EQ(my_maze.GetCols(), expected_cols);
}
