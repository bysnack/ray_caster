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
    if (!_light.loadFromFile("assets/light.png")) std::cout << "ERROR\n";
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
    castRays(3000);
  }

  /**
   * @brief           Cast a given amount of rays
   * @param amount    The amount of rays to cast
   */
  void castRays(uint32_t amount) {
    // clear old set of rays
    _rays.clear();
    triangles.clear();

    // add the rays
    float modifier = 2 * M_PI / amount;
    float angle = 359.f * M_PI / 180;
    sf::Vector2f dimensions{ RESOLUTION.first - 2.f * (RESOLUTION.first / MAP_SIZE.first), RESOLUTION.second - 2.f * (RESOLUTION.second / MAP_SIZE.second) };

    auto scale = [&](const sf::Vector2f& inter, const sf::Vector2f& pos, const sf::Vector2f& dim)->sf::Vector2f{
      auto [sx, sy] = _light.getSize();
      return { (sx / dim.x) * (inter.x - pos.x + dim.x / 2.f), (sy / dim.y) * (inter.y - pos.y + dim.y / 2.f) };
    };

    triangles.emplace_back(_position, scale(_position, _position, dimensions));
    for (auto i = 0u; i < amount; i++) {
      Ray r{ _position, angle, _current_map };
        triangles.emplace_back(r.getInter(), scale(r.getInter(), _position, dimensions));
        _rays.emplace_back(r);      

      angle += modifier;
    }

    triangles.emplace_back(triangles[1].position, scale(triangles[1].position, _position, dimensions));

  }

private:
  /**
   * @brief           Draws the user and rays to the screen
   * @param target    Target where the elements are going to be drawn
   * @param states    The states used for drawing
   */
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
    states.texture = &_light;
    target.draw(triangles.data(), triangles.size(), sf::TriangleFan, states);
    //for (auto &&ray : _rays) {
    //  target.draw(ray, states);
    //}

    target.draw(_user);
  }

  std::vector<sf::Vertex> triangles;
  sf::CircleShape _user   {10.f         };
  sf::Vector2f _position  {360.f, 260.f };
  float _speed            {10.f          };
  std::vector<Ray> _rays  {             };
  const Map &_current_map {             };
  sf::Texture _light{};
};