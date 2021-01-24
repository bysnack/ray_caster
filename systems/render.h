#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "../entities/entities.h"


namespace systems {

    void render(entities::entities& container, sf::RenderWindow& window);
}