#pragma once

#include <SFML/Graphics.hpp>
#include "../utils/vector.h"
#include "../utils/utilities.h"
#include "../components/components.h"


namespace systems {

  class movement {
    public:
      void operator()(components::container& container) {
        // only on movable components
        container.apply_if<components::is_movable>([&](auto&& elem){
          // player
          if constexpr (components::is_component_v<decltype(elem), components::player>) {
            auto [position, heading] = calculateNewPosition(elem.speed, elem.colliding, elem.heading);
            elem.position += std::move(position);
            elem.heading = heading;
          }
        });
      }

    private:
      std::tuple<utils::vector<float>, entities::heading> calculateNewPosition(float speed, bool colliding, entities::heading heading) {
        // unity advance vectors
        const utils::vector<float> x_unity{ speed, 0.f };
        const utils::vector<float> y_unity{ 0.f, speed };

        utils::vector<float> position{ 0.f, 0.f };

        // on key pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
          position += x_unity;
          heading = entities::heading::east;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
          position -= x_unity;
          heading = entities::heading::west;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
          position += y_unity;
          heading = entities::heading::south;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
          position -= y_unity;
          heading = entities::heading::north;
        }

        return { position, heading };
      }
  };
}