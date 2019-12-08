#pragma once

#include "../components/components.h"

namespace entities {

  struct player {
    components::render      render;
    components::position    position  { 400.f, 300.f                };
    components::speed       speed     { 5.f                         };
    components::colliding   colliding { false                       };
    components::heading     heading   { components::heading::north  };
    components::dimensions  dimensions{ 10.f, 10.f                  };
  };
}