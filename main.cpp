#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Map.h"
#include "User.h"
#include "Systems/Renderer.h"
#include <gsl/span>
#include <variant>
#include "SystemContainer.h"
#include "Systems/InitMap.h"
//#include "TypeList.h"
#include "Entities/Entities.h"
#include "Components/Components.h"

int main() {

  auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(RESOLUTION.first, RESOLUTION.second), "Caster");
  Map map;
  User user{ map };

  // list components
  Components::Container components{
    Entities::Map{},
    Entities::Line{},
  };

  Systems::InitMap{ components };

  // list sytstems
  SystemContainer systems{
    Systems::Renderer{ window }
  };

  while (window->isOpen()) {
    sf::Event event;
    while (window->pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window->close();
      }
    }

    systems.run_all(components);

    user.captureMovement();

  }
  return 0;
}