#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdint>
#include <vector>
#include <array>
#include "Intersection.h"
#include "Utilities.h"

static inline sf::Vector2f selectEndPoint(float angle, const sf::Vector2f& initialPos, const Map& map) {
  Intersection<Vertical>    interV{ angle, initialPos, map };
  Intersection<Horizontal>  interH{ angle, initialPos, map };

  if (distance(initialPos, interH.getPoint()) <= distance(initialPos, interV.getPoint())) {
    return interH.getPoint();
  }

  return interV.getPoint();
}

class Ray : public sf::Drawable {
public:
  Ray(const sf::Vector2f& begin, float angle, const Map& map) : 
    _line{ begin, selectEndPoint(angle, begin, map) }
  {
  }

private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override {
    target.draw(_line.data(), _line.size(), sf::Lines);
  }
  std::array<sf::Vertex, 2> _line;
  float                     _angle;
};