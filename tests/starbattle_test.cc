#include "starbattle/starbattle.h"

#include <random>

#include "gtest/gtest.h"

TEST(StarBattleTest, BoardRandomizerGenerateTest) {
  std::mt19937 test_gen(123456);
  starbattle::BoardRandomizer::GenerateBoard(10, test_gen);

  EXPECT_TRUE(true);
}
