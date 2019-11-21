#pragma once

#include <SFML/Graphics.hpp>
#include "../Utils/Vector.h"
#include "../Utils/Utilities.h"
#include "../Components/Components.h"


namespace Systems {

  class Movement {
    public:
      void run(Components::Container& components) {
        // handle movement
        components.apply<Components::Movable>([&](auto&& elem){
          elem.position += captureMovement(elem.speed);
        });
      }

    private:
      Utils::Vector<float> captureMovement(float speed) {
        // unity advance vectors
        const Utils::Vector<float> xUnity{1.f * speed, 0.f};
        const Utils::Vector<float> yUnity{0.f, 1.f * speed};

        Utils::Vector<float> result{ 0.f, 0.f };
        // on key pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
          result += xUnity;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
          result -= xUnity;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
          result += yUnity;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
          result -= yUnity;

        return result.coordinates(Utils::Coordinates::Screen);
      }
  };
}