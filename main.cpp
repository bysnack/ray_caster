#include "systems/systems.h"
#include "utils/iterable_tuple.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    auto window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode(config::RESOLUTION.first, config::RESOLUTION.second),
        "Caster");
    window->setFramerateLimit(60);

    // initialize the systems
    entities::entities entities;
    systems::systems systems { entities };

    sf::Clock clock;
    sf::Time previousTime = clock.getElapsedTime();
    sf::Time currentTime;
    float fps;

    // game loop
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
        }

        systems(entities);
        systems(entities, *window);
        currentTime = clock.getElapsedTime();
        fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds()); // the asSeconds returns a float
        std::cout
            << "fps =" << floor(fps)
            << std::endl; // flooring it will make the frame rate a rounded number
        previousTime = currentTime;
    }
    return 0;
}