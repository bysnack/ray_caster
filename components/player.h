#pragma once

#include "../entities/entities.h"

namespace components {

  struct player {
    entities::render      render;
    entities::position    position  { 400.f, 300.f  };
    entities::speed       speed     { 10.f          };
    entities::colliding   colliding { false         };
    entities::dimensions  dimensions{ 10.f, 10.f    };
  };
}