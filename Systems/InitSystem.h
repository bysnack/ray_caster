#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

using Tile = std::vector<sf::Vertex>;
namespace {

  std::vector<Tile> initializeMap(gsl::span<uint8_t> seed, const std::pair<uint32_t, uint32_t>& size) {
    const auto& [width, height] = size;
    std::vector<Tile> tiles;
    tiles.reserve(seed.size());

    for (auto i = 0u; i < seed.size(); ++i) {
      // calculate tile dimensions
      sf::Vector2f dimensions{
        static_cast<float>(RESOLUTION.first / width),
        static_cast<float>(RESOLUTION.second / height)
      };

      sf::Vector2f positions{
        (i % width) * dimensions.x,
        static_cast<uint32_t>(i / width) * dimensions.y
      };

      const auto color = seed[i] == 0 ? sf::Color::Black : sf::Color::Red;

      Tile tile{
        {{0.f                + positions.x, 0.f                + positions.y}, color},
        {{0.f + dimensions.x + positions.x, 0.f                + positions.y}, color},
        {{0.f + dimensions.x + positions.x, 0.f + dimensions.y + positions.y}, color},
        {{0.f                + positions.x, 0.f + dimensions.y + positions.y}, color},
      };

      tiles.push_back(tile);
    }
    return tiles;
  }
}

class InitSystem {
  public:
    template<class Component>
    InitSystem(Component&& components)
    {
      components.template apply<Components::Initializable>([](auto&& elem){
        initializeMap(elem.seed, elem.size);
      });
    }
};