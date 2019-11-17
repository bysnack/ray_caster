#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Map.h"
#include "User.h"
#include "Systems/DrawingSystem.h"
#include <gsl/span>
#include <variant>
#include "ComponentContainer.h"
#include "SystemContainer.h"
#include "Systems/InitSystem.h"
//#include "TypeList.h"
#include "Entities/Entities.h"
#include "Components/Components.h"

int main() {

  auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(RESOLUTION.first, RESOLUTION.second), "Caster");
  Map map;
  User user{ map };

  // list components
  ComponentContainer components{
    Entities::Map{},
    Entities::Line{},
  };

  InitSystem{ components };

  // list sytstems
  SystemContainer systems{
    DrawingSystem{ window }
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