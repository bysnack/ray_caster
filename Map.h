#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdint>
#include <vector>
#include <array>
#include "Utilities.h"


/**
  * @brief  Map class
  */
class Map : public sf::Drawable {
public:
  /**
   * @brief   Default constructor
   */
  Map() {
    _walls.reserve(_size.first * _size.second);
    for (uint32_t i = 0; i < _mini_map.size(); ++i) {
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
      if (_mini_map[i] == 0) {
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

  /**
   * @brief           Checks if a given screen coordinate is colliding with a wall
   * @param position  The coordinate to check
   * @return          A boolean indicating if the given coordinate collides with a wall
   */
  bool isColiding(const sf::Vector2f& position) const noexcept {
    auto [x, y] = toTilePos(position);

    return _mini_map[x + y * _size.first] == 1;
  }

  /**
   * @brief           Checks if a given screen coordinate is in the map bounds
   * @param position  The coordinate to check
   * @return          A boolean indicating if the given coordinate is in the map bounds
   */
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
  /**
   * @brief           Draws the user and rays to the screen
   * @param target    Target where the elements are going to be drawn
   * @param states    The states used for drawing
   */
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
    for (auto&& tile : _walls) {
      target.draw(tile, states);
    }
  }

  std::vector<sf::RectangleShape> _walls;
  std::vector<uint8_t> _mini_map {
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