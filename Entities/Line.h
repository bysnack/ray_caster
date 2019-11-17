#pragma once

#include "Properties/RenderData.h"

namespace Entities {

  struct Line {
    Properties::RenderData render{ {sf::Lines, {{{0.f, 0.f}, sf::Color::Blue }, {{800.f, 600.f}, sf::Color::Blue}}} };
  };
}