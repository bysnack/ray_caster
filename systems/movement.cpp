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
    std::tuple<utils::vector<float>, components::heading> capture_movement(float speed, components::heading heading) {
        // unity advance vectors
        const utils::vector<float> x_unity{ speed, 0.f };
        const utils::vector<float> y_unity{ 0.f, speed };

        utils::vector<float> position{ 0.f, 0.f };

        // on key pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            position += x_unity;
            heading = components::heading::east;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            position -= x_unity;
            heading = components::heading::west;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            position += y_unity;
            heading = components::heading::south;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            position -= y_unity;
            heading = components::heading::north;
        }

        return { position, heading };
    }
}

namespace systems {

    void movement(entities::entities& container) noexcept {
        // only on movable entities
        container.apply_for<components::spatial, components::heading, components::speed>([&](auto&& elem) {
            // player
            auto [position, heading] = capture_movement(std::get<components::speed>(elem), std::get<components::heading>(elem));
            std::get<components::spatial>(elem).position += std::move(position);
            std::get<components::heading>(elem) = heading;
        });
    }
}