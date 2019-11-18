#pragma once

#include <memory>
#include <variant>
#include <vector>

#include "Entities/Entities.h"
#include "ComponentTraits.h"


namespace Components {

  template<uint32_t Id, class ...Entities>
  struct Base {
    std::vector<std::variant<std::shared_ptr<Entities>...>>   entities;
  };

  struct Drawable       : public Base<0, Entities::Line, Entities::Map> {};
  struct Initializable  : public Base<1, Entities::Map>                 {};

  using Component     = std::variant<Drawable, Initializable>;
  using ComponentPtr  = std::shared_ptr<Component>;
  using Components    = std::tuple<Drawable, Initializable>;
}