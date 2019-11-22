#pragma once

#include <tuple>
#include <SFML/Graphics.hpp>


namespace entities {
  using render = std::tuple<sf::PrimitiveType, std::vector<sf::Vertex>>;
}