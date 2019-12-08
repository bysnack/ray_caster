#include <SFML/Graphics.hpp>
#include "systems/systems.h"


int main() {
    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(config::RESOLUTION.first, config::RESOLUTION.second), "Caster");
    window->setFramerateLimit(60);

    // initialize the systems
    systems::systems systems{ window };

    // game loop
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
        }

        systems.run_all();
    }
    return 0;
}