#include "Map.h"
#include "Utilities.h"

/**
 * @brief   Vertical intersection policy class
 */
struct Vertical{
  /**
   * @brief             Calculates vertical intersection point
   * @param angle       The angle between the origin and the intersection
   * @param initialPos  The origin position
   * @param map         The map where the intersections have to be calculated
   * @returns           The intersection point
   */
  sf::Vector2f intersectionPoint(float angle, const sf::Vector2f& initialPos, const Map& map) {
    float tan   = tanf(angle);
    float sin   = sinf(angle);
    float cos   = cosf(angle);

    // no intersection
    if (cmpf(cos, 0.f)) {
      return { std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest() };
    }
    
    // calculate the vertical step positions
    float x = std::round(cos);
    float y = std::round(sin);

    if (!cmpf(sin, 0.f)) {
      x = (cos / std::abs(cos));
      y = (cos / std::abs(cos)) / tan;
    }
    auto step     = toScreenCoordinates({x, y});
    
    
    // calculate the position from the start point to the grid
    auto [pX, pY] = toWorldCoordinates(initialPos);
    if (cos > 0.f) {
      x = ceilf(pX) - pX;
    } else {
      x = floorf(pX) - pX - 0.01f;
    }

    if (cmpf(sin, 0.f)) {
      y = 0.f;
    } else {
      y = x * 1.f / tan;
    }
    auto diff = toScreenCoordinates({x, y});

    // calculate intersection
    sf::Vector2f intersection{ initialPos.x + diff.x, initialPos.y + diff.y };

    while (map.isInBounds(intersection) && !map.isColiding(intersection)) {
      intersection += { step.x, step.y};
    }

    return intersection;
  }
};

/**
 * @brief   Horizontal intersection policy class
 */
struct Horizontal{
  /**
   * @brief             Calculates horizontal intersection point
   * @param angle       The angle between the origin and the intersection
   * @param initialPos  The origin position
   * @param map         The map where the intersections have to be calculated
   * @returns           The intersection point
   */
  sf::Vector2f intersectionPoint(float angle, const sf::Vector2f& initialPos, const Map& map) {
    float tan   = tanf(angle);
    float sin   = sinf(angle);
    float cos   = cosf(angle);

    // no intersection
    if (cmpf(sin, 0.f)) {
      return { std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest() };
    }
    
    // calculate the horizontal step positions
    float x = std::round(cos);
    float y = std::round(sin);

    if (!cmpf(cos, 0.f)) {
      x = (sin / std::abs(sin)) * tan;
      y = (sin / std::abs(sin));
    }
    auto step     = toScreenCoordinates({x, y});
    
    
    // calculate the position from the start point to the grid
    auto [pX, pY] = toWorldCoordinates(initialPos);
    if (sin > 0.f) {
      y = ceilf(pY) - pY + 0.01f;
    } else {
      y = floorf(pY) - pY - 0.01f;
    }

    if (cmpf(cos, 0.f)) {
      x = 0.f;
    } else {
      x = y * tan;
    }
    auto diff = toScreenCoordinates({x, y});

    // calculate intersection
    sf::Vector2f intersection{ initialPos.x + diff.x, initialPos.y + diff.y };

    while (map.isInBounds(intersection) && !map.isColiding(intersection)) {
      intersection += { step.x, step.y};
    }

    return intersection;
  }
};

/**
 * @brief   Intersection class
 */
template<class policy>
class Intersection : public policy {
  public:
    /**
     * @brief             Constructor
     * @param angle       The angle between the origin and the intersection
     * @param initialPos  The origin position
     * @param map         The map where the intersections have to be calculated
     */
    Intersection(float angle, const sf::Vector2f& initialPos, const Map& map) : 
      _position{ policy::intersectionPoint(angle, initialPos, map) }
    {}

    /**
     * @brief             Retrieves the intersection point
     */
    const sf::Vector2f& getPoint() const noexcept { return _position; }
  private:
    sf::Vector2f  _position;
};
