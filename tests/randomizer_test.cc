#include "maze/randomizer.h"

#include "gtest/gtest.h"

TEST(PrimTest, TwoByTwoRandomize) {
  int expected_cells_side = 2;
  std::mt19937 test_gen(123456);
  maze::Maze my_maze = maze::Prim::RandomizeMaze(expected_cells_side,
                                                 expected_cells_side, test_gen);
  // +───+───+
  // │       │
  // +   +───+
  // │       │
  // +───+───+
  EXPECT_EQ(my_maze.GetRows(), expected_cells_side);
  EXPECT_EQ(my_maze.GetCols(), expected_cells_side);
  EXPECT_TRUE(my_maze.IsConnected({0, 0}, {0, 1}));
  EXPECT_TRUE(my_maze.IsConnected({0, 0}, {1, 0}));
  EXPECT_TRUE(my_maze.IsConnected({1, 0}, {1, 1}));
  EXPECT_FALSE(my_maze.IsConnected({0, 1}, {1, 1}));
}
