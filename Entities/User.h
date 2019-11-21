#pragma once

#include "../Utils/Vector.h"

namespace Entities {

  struct User {
    Properties::RenderData  render;
    Utils::Vector<float>    position{ 800.f, 600.f};
    float                   speed   { 10.f        };
  };
}