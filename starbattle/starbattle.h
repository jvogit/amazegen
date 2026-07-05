#ifndef STARBATTLE_STARBATTLE_H_
#define STARBATTLE_STARBATTLE_H_

#include <random>
#include <vector>
namespace starbattle {
namespace internal {
using Graph = std::vector<int>;
}

class Board {
 private:
  internal::Graph graph_;
};

class BoardRandomizer {
 public:
  template <std::uniform_random_bit_generator G>
  inline static Board GenerateBoard(G& g) {
    std::uniform_real_distribution<float> distrib(0.0f, 1.0f);
  }
};
}  // namespace starbattle

#endif
