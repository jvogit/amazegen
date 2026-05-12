#ifndef MAZE_RANDOMIZER_H_
#define MAZE_RANDOMIZER_H_

#include <random>

#include "maze.h"

namespace maze {

class Prim {
 public:
  template <std::uniform_random_bit_generator G>
  static Maze RandomizeMaze(int rows, int cols, G& gen);

 private:
  static Maze::Graph ConstructGraph(int rows, int cols);

  template <std::uniform_random_bit_generator G>
  static void RandomizeEdgeWeights(Maze::Graph& graph, G& gen);

  static Maze::Graph ConstructMST(const Maze::Graph& graph);
};

}  // namespace maze

// template Prim functions

template <std::uniform_random_bit_generator G>
maze::Maze maze::Prim::RandomizeMaze(int rows, int cols, G& gen) {
  Maze maze(rows, cols);

  Maze::Graph graph = ConstructGraph(rows, cols);

  RandomizeEdgeWeights(graph, gen);

  maze.graph_ = ConstructMST(graph);

  return maze;
}

template <std::uniform_random_bit_generator G>
void maze::Prim::RandomizeEdgeWeights(Maze::Graph& graph, G& gen) {
  std::uniform_real_distribution<float> distrib(0.0f, 1.0f);

  for (auto& edge_list : graph) {
    for (auto& [to, weight] : edge_list) {
      weight = distrib(gen);
    }
  }
}

#endif
