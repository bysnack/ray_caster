#pragma once

#include <utility>


constexpr std::pair<uint32_t, uint32_t> RESOLUTION{ 800, 600  };
constexpr std::pair<uint32_t, uint32_t> MAP_SIZE  { 20, 20    };

static inline bool cmpf(float A, float B, float epsilon = 0.005f)
{
    return (fabs(A - B) < epsilon);
}

static inline float distance(const sf::Vector2f& begin, const sf::Vector2f& end) {
  auto& [bx, by] = begin;
  auto& [ex, ey] = end;

  return sqrtf(powf(ex - bx, 2) + powf(ey - by, 2));
}


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