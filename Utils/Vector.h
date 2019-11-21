#pragma once

#include <SFML/Graphics.hpp>
#include <type_traits>
#include <utility>
#include <string>
#include <sstream>


namespace Utils {
  
  template<class T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
  struct Vector {
    using value_type = T;
    T x, y;

    Vector(T x, T y) noexcept : 
      x{ x },
      y{ y }
    {}

    Vector(const sf::Vector2<T>& vector) noexcept :
      x{ vector.x },
      y{ vector.y }
    {}

    Vector<T>& operator+=(const Vector<T>& vector) noexcept {
      x += vector.x;
      y += vector.y;

      return *this;
    }

    Vector<T>& operator-=(const Vector<T>& vector) noexcept {
      x -= vector.x;
      y -= vector.y;

      return *this;
    }

    Vector<T>& operator*=(T multiplier) noexcept {
      x *= multiplier;
      y *= multiplier;

      return *this;
    }

    Vector<T>& operator/=(T divisor) noexcept {
      x /= divisor;
      y /= divisor;

      return *this;
    }

    Vector<T> operator+(const Vector<T>& vector) const noexcept {
      return { x + vector.x, y + vector.y };
    }

    Vector<T> operator-(const Vector<T>& vector) const noexcept {
      return { x - vector.x, y - vector.y };
    }

    Vector<T> operator*(T multiplier) const noexcept {
      return { x * multiplier, y * multiplier };
    }

    Vector<T> operator/(T dividend) const noexcept {
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
    
    Vector<float> operator%(float theta) const noexcept {
      float cs = cosf(theta);
      float sn = sinf(theta);

      return{ x * cs - y * sn, x * sn + y * cs };
    }

    bool operator==(const Vector<T>& other) const noexcept {
      return x == other.x && y == other.y;
    }

    bool operator!=(const Vector<T>& other) const noexcept {
      return !(*this == other);
    }

    Vector<T> dot(const Vector<T>& other) const noexcept {
      return { x * other.x + y * other.y };
    }

    float angle() const noexcept {
      return atan2f(x, y);
    }

    float magnitude() const noexcept {
      return sqrtf(powf(x, 2) + powf(y, 2));
    }
  };
}
