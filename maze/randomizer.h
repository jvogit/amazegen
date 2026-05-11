#ifndef MAZE_RANDOMIZER_H_
#define MAZE_RANDOMIZER_H_

#include <random>

#include "maze.h"

namespace maze {

class Prim {
 public:
  template <std::uniform_random_bit_generator G>
  static Maze Randomize(int rows, int cols, G& gen);

 private:
  static Maze::Graph ConstructGraph(int rows, int cols);

  template <std::uniform_random_bit_generator G>
  static void RandomizeEdgeWeights(Maze::Graph& graph, G& gen);
};

}  // namespace maze

#endif