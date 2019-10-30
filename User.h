#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdint>
#include <vector>
#include <array>
#include "Map.h"
#include "Ray.h"

bool cmpf(float A, float B, float epsilon = 0.005f)
{
    return (fabs(A - B) < epsilon);
}

class User : public sf::Drawable {
public:
  User(const Map& map) : 
    _current_map{ map }
  {
    _user.setFillColor(sf::Color::Blue);
    _user.setPosition(_position);
    _user.setOrigin(_user.getRadius(), _user.getRadius());
  }

  void captureMovement() noexcept {
    const sf::Vector2f xUnity{ 1.f * _speed, 0.f };
    const sf::Vector2f yUnity{ 0.f, 1.f * _speed };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))  setPosition(_position + xUnity);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))   setPosition(_position - xUnity);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))   setPosition(_position + yUnity);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))     setPosition(_position - yUnity);
  }

  void setPosition(const sf::Vector2f& pos) noexcept {
    for (uint32_t i = 0; i < 4; ++i) {
      switch(i) {
        case 0:
          if (_current_map.isColiding(pos + sf::Vector2f(0.f, _user.getRadius()))) return;
          break;
        case 1:
          if (_current_map.isColiding(pos - sf::Vector2f(0.f, _user.getRadius()))) return;
          break;
        case 2:
          if (_current_map.isColiding(pos + sf::Vector2f(_user.getRadius(), 0.f))) return;
          break;
        default:
          if (_current_map.isColiding(pos - sf::Vector2f(_user.getRadius(), 0.f))) return;
          break;
      }
    }
    _position = pos;
    _user.setPosition(_position);
    castRays();
  }

  sf::Vector2f calculateVerticalStep() {
    float tan   = tanf(angle);
    float sin   = sinf(angle);
    float cos   = cosf(angle);
    float x, y  = 0.f;

    if (!cmpf(sin, 0.f)) {
      x = (cos / std::abs(cos));
      y = (cos / std::abs(cos)) / tan;
    } else {
      x = std::round(cos);
      y = std::round(sin);
    }

    return toScreenCoordinates({x, y});
  }

  sf::Vector2f calculateHorizontalStep() {
    float tan   = tanf(angle);
    float sin   = sinf(angle);
    float cos   = cosf(angle);
    float x = std::round(cos);
    float y = std::round(sin);

    if (!cmpf(cos, 0.f)) {
      x = (sin / std::abs(sin)) * tan;
      y = (sin / std::abs(sin));
    }

    return toScreenCoordinates({x, y});
  }

  sf::Vector2f calculateHorizontalDifferential(const sf::Vector2f& playerPos) {
    auto [x, y] = toWorldCoordinates(playerPos);
    float diffX, diffY = 0.f;
    float tan   = tanf(angle);
    float sin   = sinf(angle);
    float cos   = cosf(angle);
    if (cmpf(sin, 0.f)) {
      diffY = 0.f;
      // here its not necessary to calculate a vertical diff, because there are no vertical intersections
    } else if (sin > 0.f) {
      diffY = ceilf(y) - y + 0.01f;
    } else {
      diffY = floorf(y) - y - 0.01f;
    }

    if (cmpf(cos, 0.f)) {
      diffX = 0.f;
      // here its also not necessary to calculate
    } else {
      diffX = diffY * tan;
    }

    return toScreenCoordinates({diffX, diffY});
  }

  sf::Vector2f calculateVerticalDifferential(const sf::Vector2f& playerPos) {
    auto [x, y] = toWorldCoordinates(playerPos);
    float diffX, diffY = 0.f;
    float tan   = tanf(angle);
    float sin   = sinf(angle);
    float cos   = cosf(angle);
    if (cmpf(cos, 0.f)) {
      diffX = 0.f;
      // here its not necessary to calculate a vertical diff, because there are no vertical intersections
    } else if (cos > 0.f) {
      diffX = ceilf(x) - x;
    } else {
      diffX = floorf(x) - x - 0.01f;
    }

    if (cmpf(sin, 0.f)) {
      diffY = 0.f;
      // here its also not necessary to calculate
    } else {
      diffY = diffX * 1.f / tan;
    }

    return toScreenCoordinates({diffX, diffY});
  }

  void incrementAngle() {
    if (angle < 2.f * M_PI) {
      angle += 0.1f;
    } else {
      angle = 0.f;
    }
    std::cout << "ANGLE: " << angle << "\n";
  }

  sf::Vector2f calculateIntersection(const sf::Vector2f& step, const sf::Vector2f& diff) {
    sf::Vector2f intersection{ _position.x + diff.x, _position.y + diff.y };

    while (_current_map.isInBounds(intersection) && !_current_map.isColiding(intersection)) {
      intersection += { step.x, step.y};
    }

    return intersection;
  }

  void castRays() {
    _rays.clear();
    _intersections.clear();
    std::cout << _position.x << " " << _position.y << "\n";

    float modifier = 2 * M_PI / 100;
    angle = M_PI / 2.f;
    for (auto i = 0u; i < 100; i++) {
      angle += modifier;
      sf::Vector2f verticalIntersection{-10000.f, -10000.f};
      if (!cmpf(cosf(angle), 0.f)) {
        verticalIntersection = calculateIntersection(calculateVerticalStep(), calculateVerticalDifferential(_position));
      }
      sf::Vector2f horizontalIntersection{-10000.f, -10000.f};
      if (!cmpf(sinf(angle), 0.f)) {
        horizontalIntersection = calculateIntersection(calculateHorizontalStep(), calculateHorizontalDifferential(_position));
      }

      auto& selected = distance(_position, horizontalIntersection) <= distance(_position, verticalIntersection) ? horizontalIntersection : verticalIntersection;
      _rays.emplace_back(_position, selected);
    }
  }

private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override {
    target.draw(_user);
    
    for (auto&& ray : _rays) {
      target.draw(ray);
    }
    for (auto&& inter : _intersections) {
      target.draw(inter, state);
    }
  }
  
  std::vector<sf::RectangleShape> _intersections;
  sf::CircleShape   _user         { 10.f          };
  sf::Vector2f      _position     { 400.f, 300.f  };
  float             _speed        { 5.f           };
  std::vector<Ray>  _rays         {               };
  const Map         &_current_map                  ;
  float angle = 0.f;

};