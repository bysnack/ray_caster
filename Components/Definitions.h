#pragma once

#include "Component.h"

namespace Components {

  using Drawable    = Component<Entities::Line, Entities::Map, Entities::User>;
  using Map         = Component<Entities::Map>;
  using User        = Component<Entities::User>;
}