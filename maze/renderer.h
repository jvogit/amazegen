#ifndef MAZE_RENDERER_H_
#define MAZE_RENDERER_H_

#include <ostream>

#include "maze.h"

namespace maze::renderer {

void Render(std::ostream& os, maze::Maze& maze);

}  // namespace maze::renderer

#endif