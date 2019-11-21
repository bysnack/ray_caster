#pragma once

#include <vector>
#include <SFML/Graphics.hpp>


namespace Entities::Properties {
  using Renderizable  = std::tuple<sf::PrimitiveType, std::vector<sf::Vertex>>;
  using RenderData    = std::vector<Renderizable>;
}