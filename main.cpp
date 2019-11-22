#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <gsl/span>
#include <variant>
#include "utils/utilities.h"
#include "systems/systems.h"
#include "entities/entities.h"
#include "components/components.h"

int main() {

  auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(utils::RESOLUTION.first, utils::RESOLUTION.second), "Caster");
  window->setFramerateLimit(60);

  // list components
  components::container components;

  components.insert_or_replace(components::player{}, 0);

  systems::initialize_map(components);

  // list sytstems
  systems::container systems{
    systems::render{ window },
    systems::movement{}
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