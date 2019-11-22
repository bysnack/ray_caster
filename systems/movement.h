#pragma once

#include <SFML/Graphics.hpp>
#include "../utils/vector.h"
#include "../utils/utilities.h"
#include "../components/components.h"


namespace systems {

  class movement {
    public:
      void run(components::container& components) {
        // handle movement
        components.apply_if<components::is_movable>([&](auto&& elem){
          elem.position += captureMovement(elem.speed);
        });
      }

    private:
      utils::vector<float> captureMovement(float speed) {
        // unity advance vectors
        const utils::vector<float> x_unity{1.f * speed, 0.f};
        const utils::vector<float> y_unity{0.f, 1.f * speed};

        utils::vector<float> result{ 0.f, 0.f };
        // on key pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
          result += x_unity;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
          result -= x_unity;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
          result += y_unity;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
          result -= y_unity;

        return result.coordinates(utils::coordinates::screen);
      }
  };
}