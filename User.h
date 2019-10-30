#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdint>
#include <vector>
#include <array>
#include "Map.h"
#include "Ray.h"
#include "Utilities.h"


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
    castRays(1000);
  }

  void castRays(uint32_t amount) {
    // clear old set of rays
    _rays.clear();

    // add the rays
    float modifier = 2 * M_PI / amount;
    float angle = M_PI / 2.f;
    for (auto i = 0u; i < amount; i++) {
      angle += modifier;
      _rays.emplace_back(_position, angle, _current_map);
    }
  }

private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override {
    for (auto&& ray : _rays) {
      target.draw(ray);
    }
    target.draw(_user);
  }
  
  sf::CircleShape   _user         { 10.f          };
  sf::Vector2f      _position     { 400.f, 300.f  };
  float             _speed        { 5.f           };
  std::vector<Ray>  _rays         {               };
  const Map         &_current_map                  ;
};