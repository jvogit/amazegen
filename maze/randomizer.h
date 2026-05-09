#ifndef MAZE_RANDOMIZER_H_
#define MAZE_RANDOMIZER_H_

#include "maze.h"

namespace maze {

class Prim {
 public:
  void Randomize(Maze& maze) const;
};

}  // namespace maze

#endif