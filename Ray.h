#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdint>
#include <vector>
#include <array>

class Ray : public sf::Drawable {
public:
  Ray(const sf::Vector2f& begin, const sf::Vector2f& end) : 
    _line{ begin, end }
  {

  }

  float getAngle() const noexcept {
    return _angle;
  }
private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override {
    target.draw(_line.data(), _line.size(), sf::Lines);
  }
  std::array<sf::Vertex, 2> _line;
  float                     _angle;
};