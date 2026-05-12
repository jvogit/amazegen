#include "maze/maze.h"

#include "gtest/gtest.h"

TEST(MazeTest, Initialization) {
  int expected_rows = 3;
  int expected_cols = 2;
  maze::Maze my_maze(expected_rows, expected_cols);

  EXPECT_EQ(my_maze.GetRows(), expected_rows);
  EXPECT_EQ(my_maze.GetCols(), expected_cols);
}

TEST(MazeTest, IsConnected) {
  int expected_cells_side = 2;
  maze::Maze my_maze(expected_cells_side, expected_cells_side);

  EXPECT_EQ(my_maze.GetRows(), expected_cells_side);
  EXPECT_EQ(my_maze.GetCols(), expected_cells_side);
  EXPECT_FALSE(my_maze.IsConnected({0, 0}, {0, 1}));
  EXPECT_FALSE(my_maze.IsConnected({1, 0}, {0, 0}));
}
