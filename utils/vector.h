#pragma once

#include <SFML/Graphics.hpp>
#include <type_traits>
#include <utility>
#include <string>
#include <iostream>
#include <sstream>
#include "utilities.h"


namespace utils {

  enum class coordinates : uint8_t {
    world,
    screen,
  };
  
  template<class T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
  struct vector {
    using value_type = T;
    T x, y;

    vector(T x, T y) noexcept : 
      x{ x },
      y{ y }
    {}

    vector(const sf::Vector2<T>& other) noexcept :
      x{ other.x },
      y{ other.y }
    {}

    vector<T>& operator+=(const vector<T>& other) noexcept {
      x += other.x;
      y += other.y;

      return *this;
    }

    vector<T>& operator-=(const vector<T>& other) noexcept {
      x -= other.x;
      y -= other.y;

      return *this;
    }

    vector<T>& operator*=(T multiplier) noexcept {
      x *= multiplier;
      y *= multiplier;

      return *this;
    }

    vector<T>& operator/=(T divisor) noexcept {
      x /= divisor;
      y /= divisor;

      return *this;
    }

    vector<T> operator+(const vector<T>& other) const noexcept {
      return { x + other.x, y + other.y };
    }

    vector<T> operator-(const vector<T>& other) const noexcept {
      return { x - other.x, y - other.y };
    }

    vector<T> operator*(T multiplier) const noexcept {
      return { x * multiplier, y * multiplier };
    }

    vector<T> operator/(T dividend) const noexcept {
      return { x * dividend, y * dividend };
    }

    operator sf::Vector2f() const noexcept { 
      return { x, y }; 
    } 

    operator std::string() const noexcept {
      std::stringstream ss;
      ss << "X: " << x << " - " << "Y: " << y;

      return ss.str();
    }
    
    vector<float> operator%(float theta) const noexcept {
      float cs = cosf(theta);
      float sn = sinf(theta);

      return{ x * cs - y * sn, x * sn + y * cs };
    }

    bool operator==(const vector<T>& other) const noexcept {
      return x == other.x && y == other.y;
    }

    bool operator!=(const vector<T>& other) const noexcept {
      return !(*this == other);
    }

    vector<T> dot(const vector<T>& other) const noexcept {
      return { x * other.x + y * other.y };
    }

    float angle() const noexcept {
      return atan2f(x, y);
    }

    float magnitude() const noexcept {
      return sqrtf(powf(x, 2) + powf(y, 2));
    }

    friend std::ostream& operator<<(std::ostream& os, const vector<T>& vector) {
      os << std::string{ vector };
      return os;
    }

    vector<T> coordinates(coordinates type, std::enable_if_t<std::is_floating_point_v<T>>* = 0) {
      switch(type) {
        case coordinates::world:
          return { (x * RESOLUTION.first) / MAP_SIZE.first, (y * RESOLUTION.second) / MAP_SIZE.second };
        case coordinates::screen:
          return { (x * MAP_SIZE.first) / RESOLUTION.first, (y * MAP_SIZE.second) / RESOLUTION.second };
        default:
          return { -1.f, -1.f };
      }
    }
  };
}
