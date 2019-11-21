#pragma once

#include "Properties/RenderData.h"
#include "../Utils/Vector.h"

namespace Entities {

  struct Line {
    Line(const Utils::Vector<float>& begin, const Utils::Vector<float>& end) noexcept :
      render{ {sf::Lines, {{begin, sf::Color::Blue }, {end, sf::Color::Blue}}} }
    {}
    Properties::RenderData render;
  };
}