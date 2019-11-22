#pragma once

#include "../entities/render.h"
#include "../entities/position.h"
#include "../entities/speed.h"

namespace components {

  struct player {
    entities::render    render;
    entities::position  position{ 400.f, 300.f  };
    entities::speed     speed   { 10.f          };
  };
}