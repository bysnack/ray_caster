#pragma once

#include <utility>
#include "../config.h"

namespace utils {
  /**
  * @brief          Compares two floating point numbers with a given epsilon
  * @param lhs      The left hand side element to comparate
  * @param rhs      The right hand side element to comparate
  * @param epsilon  The epsilon to take in account for the comparison
  * @returns        A boolean indicator of the comparision results
  */
  inline bool cmpf(float lhs, float rhs, float epsilon = 0.00005f)
  {
      return (fabs(lhs - rhs) < epsilon);
  }


  /**
  * @brief          Calculates the distance between two points in a plane
  * @param begin    The origin point
  * @param end      The final point
  * @returns        The distance between both points
  */
  inline float distance(const sf::Vector2f& begin, const sf::Vector2f& end) {
    auto& [bx, by] = begin;
    auto& [ex, ey] = end;

    return sqrtf(powf(ex - bx, 2) + powf(ey - by, 2));
  }

  /**
  * @brief                     Transforms screen coordinates to world coordinates
  * @param screenCoordinates   The screen coordinats to transform
  * @returns                   The transformed world coordinates
  */
  sf::Vector2f toWorldCoordinates(const sf::Vector2f& screenCoordinates) {
    return { (screenCoordinates.x * config::MAP_SIZE.first) / config::RESOLUTION.first, (screenCoordinates.y * config::MAP_SIZE.second) / config::RESOLUTION.second };
  }

  /**
  * @brief                     Transforms world coordinates to screen coordinates
  * @param worldCoordinates    The world coordinats to transform
  * @returns                   The transformed screen coordinates
  */
  sf::Vector2f toScreenCoordinates(const sf::Vector2f& worldCoordinates) {
    return { (worldCoordinates.x * config::RESOLUTION.first) / config::MAP_SIZE.first, (worldCoordinates.y * config::RESOLUTION.second) / config::MAP_SIZE.second };
  }

  /**
  * @brief                     Transforms pixel position to tile position
  * @param pixelPos            The pixel position to transform
  * @returns                   The transformed tile position
  */
  sf::Vector2u toTilePos(const sf::Vector2f& pixelPos) {
    uint32_t x = static_cast<uint32_t>((pixelPos.x * config::MAP_SIZE.first) / config::RESOLUTION.first);
    uint32_t y = static_cast<uint32_t>((pixelPos.y * config::MAP_SIZE.second) / config::RESOLUTION.second);
    return { x, y };
  }
}
