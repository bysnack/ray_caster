#pragma once

#include "Map.h"
#include "Ray.h"
#include "Utilities.h"
#include <SFML/Graphics.hpp>
#include <array>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

/**
 * @brief  User class
 */
class User : public sf::Drawable {
public:
  /**
   * @brief         Constructor
   */
  User(const Map &map) noexcept : _current_map{map} {
    // set user properties
    _user.setFillColor(sf::Color::Blue);
    _user.setPosition(_position);
    _user.setOrigin(_user.getRadius(), _user.getRadius());
  }

  /**
   * @brief         Captures keyboard input used to move the player around
   */
  void captureMovement() noexcept {
    // unity advance vectors
    const sf::Vector2f xUnity{1.f * _speed, 0.f};
    const sf::Vector2f yUnity{0.f, 1.f * _speed};

    // on key pressed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
      setPosition(_position + xUnity);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
      setPosition(_position - xUnity);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
      setPosition(_position + yUnity);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
      setPosition(_position - yUnity);
  }

  /**
   * @brief           Sets the current user position to a given position
   * @param position  Screen coordinates where the user is going to be positioned
   */
  void setPosition(const sf::Vector2f &position) noexcept {
    // check for collisions
    for (uint32_t i = 0; i < 4; ++i) {
      switch (i) {
      case 0:
        if (_current_map.isColiding(position +
                                    sf::Vector2f(0.f, _user.getRadius())))
          return;
        break;
      case 1:
        if (_current_map.isColiding(position -
                                    sf::Vector2f(0.f, _user.getRadius())))
          return;
        break;
      case 2:
        if (_current_map.isColiding(position +
                                    sf::Vector2f(_user.getRadius(), 0.f)))
          return;
        break;
      default:
        if (_current_map.isColiding(position -
                                    sf::Vector2f(_user.getRadius(), 0.f)))
          return;
        break;
      }
    }

    // update user position
    _position = position;

    // update circle position in screen
    _user.setPosition(_position);

    // cast rays on player position change to avoid unused of calculations
    castRays(1000);
  }

  /**
   * @brief           Cast a given amount of rays
   * @param amount    The amount of rays to cast
   */
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
  /**
   * @brief           Draws the user and rays to the screen
   * @param target    Target where the elements are going to be drawn
   */
  virtual void draw(sf::RenderTarget &target, sf::RenderStates) const override {
    for (auto &&ray : _rays) {
      target.draw(ray);
    }
    target.draw(_user);
  }

  sf::CircleShape _user{10.f};
  sf::Vector2f _position{400.f, 300.f};
  float _speed{5.f};
  std::vector<Ray> _rays{};
  const Map &_current_map{};
};