#ifndef MAZE_RENDERER_H_
#define MAZE_RENDERER_H_

#include <ostream>

#include "maze.h"

namespace maze::renderer {

std::ostream& Render(std::ostream& os, const Maze& maze);

}  // namespace maze::renderer

#endif