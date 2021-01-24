#pragma once

#include "../components/components.h"
#include <SFML/Graphics/Texture.hpp>

namespace components {

struct light {
  components::render render;
  components::dimensions dimensions{40.f, 30.f};
  std::unique_ptr<sf::Texture> texture;
};
} // namespace components