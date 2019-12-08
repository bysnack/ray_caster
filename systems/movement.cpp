#include <SFML/Graphics.hpp>

#include "movement.h"
#include "../utils/vector.h"
#include "../utils/utilities.h"
#include "../components/components.h"

/*
*   Anonymous namespace
*
*   @brief  Contains a set of helper functions used by the movement system
*/
namespace {
    std::tuple<utils::vector<float>, entities::heading> capture_movement(float speed, entities::heading heading) {
        // unity advance vectors
        const utils::vector<float> x_unity{ speed, 0.f };
        const utils::vector<float> y_unity{ 0.f, speed };

        utils::vector<float> position{ 0.f, 0.f };

        // on key pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            position += x_unity;
            heading = entities::heading::east;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            position -= x_unity;
            heading = entities::heading::west;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            position += y_unity;
            heading = entities::heading::south;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            position -= y_unity;
            heading = entities::heading::north;
        }

        return { position, heading };
    }
}

namespace systems {
    void movement(components::container& container) noexcept {
        // only on movable components
        container.apply_if<components::is_movable>([&](auto&& elem) {
            // player
            if constexpr (components::is_component_v<decltype(elem), components::player>) {
                auto [position, heading] = capture_movement(elem.speed, elem.heading);
                elem.position += std::move(position);
                elem.heading = heading;
            }
        });
    }
}