#pragma once

#include <memory>
#include <variant>
#include <vector>

#include "Entities/Entities.h"


namespace Components {

  template<class ...Entities>
  struct Component {
    std::vector<std::variant<std::shared_ptr<Entities>...>>   entities;
  };

  using Drawable = Component<Entities::Line, Entities::Map, Entities::User>;
  using Map      = Component<Entities::Map>;
  using User     = Component<Entities::User>;

  using Components    = std::tuple<Drawable, Map, User>;
}