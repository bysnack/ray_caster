#pragma once

#include "../entities/entities.h"

namespace components {

  struct player {
    entities::render      render;
    entities::position    position  { 400.f, 300.f              };
    entities::speed       speed     { 1.f                      };
    entities::colliding   colliding { false                     };
    entities::heading     heading   { entities::heading::north  };
    entities::dimensions  dimensions{ 10.f, 10.f                };
  };
}