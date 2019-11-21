#pragma once

#include "../Utils/Vector.h"

namespace Entities {

  struct User {
    Properties::RenderData  render;
    Utils::Vector<float>    position{ 0.f, 0.f};
    float                   speed   { 10.f    };
  };
}