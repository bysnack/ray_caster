#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdint>
#include <vector>
#include <array>

constexpr std::pair<uint32_t, uint32_t> RESOLUTION{ 800, 600  };
constexpr std::pair<uint32_t, uint32_t> MAP_SIZE  { 20, 20    };

static sf::Vector2f toWorldCoordinates(const sf::Vector2f& screenCoordinates) {
  return { (screenCoordinates.x * MAP_SIZE.first) / RESOLUTION.first, (screenCoordinates.y * MAP_SIZE.second) / RESOLUTION.second };
}

static sf::Vector2f toScreenCoordinates(const sf::Vector2f& worldCoordinates) {
  return { (worldCoordinates.x * RESOLUTION.first) / MAP_SIZE.first, (worldCoordinates.y * RESOLUTION.second) / MAP_SIZE.second };
}

static sf::Vector2u toTilePos(const sf::Vector2f& pixelPos) {
  uint32_t x = static_cast<uint32_t>((pixelPos.x * MAP_SIZE.first) / RESOLUTION.first);
  uint32_t y = static_cast<uint32_t>((pixelPos.y * MAP_SIZE.second) / RESOLUTION.second);
  return { x, y };
}

static sf::Vector2f toPixelPos(const sf::Vector2f& mapPos) {
  return { 
  (mapPos.x * RESOLUTION.first) / MAP_SIZE.first, 
  (mapPos.y * RESOLUTION.second) / MAP_SIZE.second
  };
}

class Map : public sf::Drawable {
public:

  Map() {
    _walls.reserve(_size.first * _size.second);
    for (uint32_t i = 0; i < _mini_walls.size(); ++i) {
      // set tile dimensions
      sf::Vector2f dimensions{ RESOLUTION.first / _size.first, RESOLUTION.second / _size.second };

      // create rectangle of tile size
      sf::RectangleShape tile{ dimensions };

      // set its position
      tile.setPosition(
        (i % _size.first) * dimensions.x,
        static_cast<uint32_t>(i / _size.first) * dimensions.y
      );
      // continue if this is not a wall
      if (_mini_walls[i] == 0) {
              // set tile color
      tile.setFillColor(sf::Color::Black);
      } else {
      // set tile color
      tile.setFillColor(sf::Color::Red);
      }      


      tile.setOutlineColor(sf::Color::Black);

      tile.setOutlineThickness(1);

      // add it to the map
      _walls.push_back(tile);
    }
  }

  bool isColiding(const sf::Vector2f& position) const noexcept {
    auto [x, y] = toTilePos(position);

    return _mini_walls[x + y * _size.first] == 1;
  }

  bool isInBounds(const sf::Vector2f& position) const noexcept {
    auto [x, y] = toTilePos(position);
    if (x > MAP_SIZE.first || y > MAP_SIZE.first) {
      return false;
    }
    if (x < 0.f || y < 0.f) {
      return false;
    }
    return true;
  }

private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
    for (auto&& tile : _walls) {
      target.draw(tile, states);
    }
  }

  std::vector<sf::RectangleShape> _walls;

  std::vector<uint8_t> _mini_walls{
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,
    1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  };

  static constexpr std::pair<uint32_t, uint32_t> _size{ 20, 20 };
};