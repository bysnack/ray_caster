#pragma once

#include "../entities/render.h"

namespace components {

  struct cell {
    entities::render      render;
    entities::position    position;
    entities::dimensions  dimensions;
  };
}