#pragma once

#include <utility>

/**
 * @brief             Configuration definitions
 */
constexpr std::pair<uint32_t, uint32_t> RESOLUTION{ 800, 600  };
constexpr std::pair<uint32_t, uint32_t> MAP_SIZE  { 20, 20    };

/**
 * @brief          Compares two floating point numbers with a given epsilon
 * @param lhs      The left hand side element to comparate
 * @param rhs      The right hand side element to comparate
 * @param epsilon  The epsilon to take in account for the comparison
 * @returns        A boolean indicator of the comparision results
 */
static inline bool cmpf(float lhs, float rhs, float epsilon = 0.005f)
{
    return (fabs(lhs - rhs) < epsilon);
}


/**
 * @brief          Calculates the distance between two points in a plane
 * @param begin    The origin point
 * @param end      The final point
 * @returns        The distance between both points
 */
static inline float distance(const sf::Vector2f& begin, const sf::Vector2f& end) {
  auto& [bx, by] = begin;
  auto& [ex, ey] = end;

  return sqrtf(powf(ex - bx, 2) + powf(ey - by, 2));
}

/**
 * @brief                     Transforms screen coordinates to world coordinates
 * @param screenCoordinates   The screen coordinats to transform
 * @returns                   The transformed world coordinates
 */
static sf::Vector2f toWorldCoordinates(const sf::Vector2f& screenCoordinates) {
  return { (screenCoordinates.x * MAP_SIZE.first) / RESOLUTION.first, (screenCoordinates.y * MAP_SIZE.second) / RESOLUTION.second };
}

/**
 * @brief                     Transforms world coordinates to screen coordinates
 * @param worldCoordinates    The world coordinats to transform
 * @returns                   The transformed screen coordinates
 */
static sf::Vector2f toScreenCoordinates(const sf::Vector2f& worldCoordinates) {
  return { (worldCoordinates.x * RESOLUTION.first) / MAP_SIZE.first, (worldCoordinates.y * RESOLUTION.second) / MAP_SIZE.second };
}

/**
 * @brief                     Transforms pixel position to tile position
 * @param pixelPos            The pixel position to transform
 * @returns                   The transformed tile position
 */
static sf::Vector2u toTilePos(const sf::Vector2f& pixelPos) {
  uint32_t x = static_cast<uint32_t>((pixelPos.x * MAP_SIZE.first) / RESOLUTION.first);
  uint32_t y = static_cast<uint32_t>((pixelPos.y * MAP_SIZE.second) / RESOLUTION.second);
  return { x, y };
}
