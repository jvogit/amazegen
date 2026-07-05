#ifndef STARBATTLE_RENDERER_H
#define STARBATTLE_RENDERER_H

#include "starbattle.h"

namespace renderer {

std::ostream& Render(std::ostream& os, const starbattle::Board& board);

}

#endif