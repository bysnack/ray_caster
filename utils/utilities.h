#pragma once

#include "../config.h"
#include <cmath>
#include <utility>

namespace utils {
/**
 * @brief          Compares two floating point numbers with a given epsilon
 * @param lhs      The left hand side element to comparate
 * @param rhs      The right hand side element to comparate
 * @param epsilon  The epsilon to take in account for the comparison
 * @returns        A boolean indicator of the comparision results
 */
inline bool cmpf(float lhs, float rhs, float epsilon = 0.0005f) {
  return (fabs(lhs - rhs) < epsilon);
}

/**
 * @brief          Calculates the distance between two points in a plane
 * @param begin    The origin point
 * @param end      The final point
 * @returns        The distance between both points
 */
template <class Coordinates>
inline float distance(const Coordinates &begin, const Coordinates &end) {
  auto &[bx, by] = begin;
  auto &[ex, ey] = end;

  return sqrtf(powf(ex - bx, 2) + powf(ey - by, 2));
}

/**
 * @brief          Calculates the squared distance between two points in a plane
 * @param begin    The origin point
 * @param end      The final point
 * @returns        The distance between both points
 */
template <class Coordinates>
inline float squared_distance(const Coordinates &begin,
                              const Coordinates &end) {
  auto &[bx, by] = begin;
  auto &[ex, ey] = end;

  return powf(ex - bx, 2) + powf(ey - by, 2);
}

/**
 * @brief          Checks whether the second argument is closer to the first
 * argument than the third argument
 *
 * @param origin   The origin point to use for comparison
 * @param lhs      The point to check
 * @param rhs      The point to checkc against
 * @returns        Whether lhs is closer to origin than rhs
 */
template <class Coordinates>
inline bool is_closer(const Coordinates &origin, const Coordinates &lhs,
                      const Coordinates &rhs) noexcept {
  auto &[ox, oy] = origin;
  auto &[lx, ly] = lhs;
  auto &[rx, ry] = rhs;

  return powf(lx - ox, 2) + powf(ly - oy, 2) <
         powf(rx - ox, 2) + powf(ry - oy, 2);
}
/**
 * @brief                     Transforms screen coordinates to world coordinates
 * @param screenCoordinates   The screen coordinats to transform
 * @returns                   The transformed world coordinates
 */
inline sf::Vector2f toWorldCoordinates(const sf::Vector2f &screenCoordinates) {
  return {(screenCoordinates.x * config::MAP_SIZE.first) /
              config::RESOLUTION.first,
          (screenCoordinates.y * config::MAP_SIZE.second) /
              config::RESOLUTION.second};
}

/**
 * @brief                     Transforms world coordinates to screen coordinates
 * @param worldCoordinates    The world coordinats to transform
 * @returns                   The transformed screen coordinates
 */
inline sf::Vector2f toScreenCoordinates(const sf::Vector2f &worldCoordinates) {
  return {(worldCoordinates.x * config::RESOLUTION.first) /
              config::MAP_SIZE.first,
          (worldCoordinates.y * config::RESOLUTION.second) /
              config::MAP_SIZE.second};
}

/**
 * @brief                     Transforms pixel position to tile position
 * @param pixelPos            The pixel position to transform
 * @returns                   The transformed tile position
 */
inline sf::Vector2u toTilePos(const sf::Vector2f &pixelPos) {
  uint32_t x = static_cast<uint32_t>((pixelPos.x * config::MAP_SIZE.first) /
                                     config::RESOLUTION.first);
  uint32_t y = static_cast<uint32_t>((pixelPos.y * config::MAP_SIZE.second) /
                                     config::RESOLUTION.second);
  return {x, y};
}
} // namespace utils
