#ifndef MAZE_RANDOMIZER_H_
#define MAZE_RANDOMIZER_H_

#include <random>

#include "maze.h"

namespace maze {

namespace internal {

maze::internal::Graph ConstructGraph(int rows, int cols);

template <std::uniform_random_bit_generator G>
void RandomizeEdgeWeights(maze::internal::Graph& graph, G& gen) {
  std::uniform_real_distribution<float> distrib(0.0f, 1.0f);

  for (auto& edge_list : graph) {
    for (auto& [to, weight] : edge_list) {
      weight = distrib(gen);
    }
  }
}

}  // namespace internal

class Prim {
 public:
  template <std::uniform_random_bit_generator G>
  inline static Maze RandomizeMaze(int rows, int cols, G& gen) {
    Maze maze(rows, cols);
    maze::internal::Graph graph = internal::ConstructGraph(rows, cols);
    internal::RandomizeEdgeWeights(graph, gen);
    maze.graph_ = ConstructMST(graph);

    return maze;
  }

 private:
  static maze::internal::Graph ConstructMST(const maze::internal::Graph& graph);
};

class Kruskal {
 public:
  template <std::uniform_random_bit_generator G>
  inline static Maze RandomizeMaze(int rows, int cols, G& gen) {
    Maze maze(rows, cols);
    maze::internal::Graph graph = internal::ConstructGraph(rows, cols);
    internal::RandomizeEdgeWeights(graph, gen);
    maze.graph_ = ConstructMST(graph);

    return maze;
  }

 private:
  static maze::internal::Graph ConstructMST(const maze::internal::Graph& graph);
};

}  // namespace maze

#endif
