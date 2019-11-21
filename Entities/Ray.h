#pragma once

#include <SFML/Graphics.hpp>

#include "Properties/RenderData.h"


namespace Entities {

  struct Ray {
    Properties::RenderData  render;
    float                   angle { 0.f };
  };
}