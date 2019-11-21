#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Systems/Renderer.h"
#include <gsl/span>
#include <variant>
#include "Utils/Utilities.h"
#include "SystemContainer.h"
#include "Systems/InitMap.h"
#include "Systems/Movement.h"
#include "Systems/InitUser.h"
#include "Entities/Entities.h"
#include "Components/Components.h"

int main() {

  auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(Utils::RESOLUTION.first, Utils::RESOLUTION.second), "Caster");

  // list components
  Components::Container components{
    Entities::Map{},
    Entities::Line{{0.f, 0.f}, {800.f, 600.f}},
    Entities::Line{{400.f, 200.f}, {0.f, 800.f}},
    Entities::User{},
  };

  Systems::InitMap  { components };
  Systems::InitUser { components };

  // list sytstems
  SystemContainer systems{
    Systems::Renderer{ window },
    Systems::Movement{}
  };

  while (window->isOpen()) {
    sf::Event event;
    while (window->pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window->close();
      }
    }

    systems.run_all(components);
  }
  return 0;
}