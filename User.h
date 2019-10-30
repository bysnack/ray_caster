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
    castRays();
  }

  void incrementAngle() {
    if (angle < 2.f * M_PI) {
      angle += 0.1f;
    } else {
      angle = 0.f;
    }
    std::cout << "ANGLE: " << angle << "\n";
  }


  void castRays() {
    _rays.clear();
    _intersections.clear();

    float modifier = 2 * M_PI / 100;
    angle = M_PI / 2.f;
    for (auto i = 0u; i < 100; i++) {
      angle += modifier;
      Intersection<Vertical>    interV{ angle, _position, _current_map };
      Intersection<Horizontal>  interH{ angle, _position, _current_map };
      auto& selected = distance(_position, interH.getPoint()) <= distance(_position, interV.getPoint()) ? interH.getPoint() : interV.getPoint();

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