#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdint>
#include <vector>
#include <array>
#include "Intersection.h"
#include "Utilities.h"

/**
 * @brief             Selects the intersection point closest to the origin
 * @param angle       The angle between the origin and the intersection
 * @param initialPos  The origin position
 * @param map         The map where the intersections have to be calculated
 * @returns           The intersection point closest to the origin
 */
static inline sf::Vector2f selectEndPoint(float angle, const sf::Vector2f& initialPos, const Map& map) {
  Intersection<Vertical>    interV{ angle, initialPos, map };
  Intersection<Horizontal>  interH{ angle, initialPos, map };

  if (distance(initialPos, interH.getPoint()) <= distance(initialPos, interV.getPoint())) {
    return interH.getPoint();
  }

  return interV.getPoint();
}

/**
 * @brief             Ray class
 */
class Ray : public sf::Drawable {
public:
  /**
   * @brief           Constructor
   */
  Ray(const sf::Vector2f& begin, float angle, const Map& map) : 
    _line{ begin, selectEndPoint(angle, begin, map) }
  {
  }

private:
  /**
   * @brief           Draws the user and rays to the screen
   * @param target    Target where the elements are going to be drawn
   * @param states    The states used for drawing
   */
  virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override {
    target.draw(_line.data(), _line.size(), sf::Lines);
  }
  std::array<sf::Vertex, 2> _line   { };
  float                     _angle  { };
};