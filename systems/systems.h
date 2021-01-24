#pragma once

#include <memory>

#include "../entities/entities.h"
#include "collision.h"
#include "lights.h"
#include "movement.h"
#include "render.h"

namespace systems {

class systems {
public:
  systems(entities::entities &container);

  void operator()(entities::entities &container) {
    movement(container);
    collision(container);
    lights(container);
  }

  void operator()(entities::entities &container, sf::RenderWindow &window) {
    render(container, window);
  }
};
} // namespace systems
