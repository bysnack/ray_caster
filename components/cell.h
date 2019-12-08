#pragma once

#include "../entities/render.h"
#include "../config.h"

namespace components {

  struct cell {
    entities::render      render;
    entities::position    position;
    entities::dimensions  dimensions;
  };
}

