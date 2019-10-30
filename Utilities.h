#pragma once

static inline bool cmpf(float A, float B, float epsilon = 0.005f)
{
    return (fabs(A - B) < epsilon);
}

static inline float distance(const sf::Vector2f& begin, const sf::Vector2f& end) {
  auto& [bx, by] = begin;
  auto& [ex, ey] = end;

  return sqrtf(powf(ex - bx, 2) + powf(ey - by, 2));
}