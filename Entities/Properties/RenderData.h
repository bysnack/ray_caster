#pragma once

#include <vector>
#include <SFML/Graphics.hpp>


namespace Entities::Properties {

  using RenderData = std::vector<std::tuple<sf::PrimitiveType, std::vector<sf::Vertex>>>;
}