#include "starbattle/starbattle.h"

#include <random>

#include "gtest/gtest.h"

TEST(StarBattleTest, BoardRandomizerGenerateTest) {
  std::mt19937 test_gen(123456);
  auto board = starbattle::BoardRandomizer::GenerateBoard(5, test_gen);

  LOG(INFO) << "\n" << board;

  EXPECT_TRUE(true);
}
