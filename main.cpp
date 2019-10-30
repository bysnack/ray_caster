#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Map.h"
#include "User.h"


int main() {
  
  sf::RenderWindow window(sf::VideoMode(RESOLUTION.first, RESOLUTION.second), "Caster");
  Map map;
  User user{ map };

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      user.captureMovement();
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear(sf::Color::Black);

    window.draw(map);
    window.draw(user);

    window.display();
  }
  return 0;
}