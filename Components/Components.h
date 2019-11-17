#pragma once

#include <memory>
#include <variant>
#include <vector>

#include "Entities/Entities.h"
#include "ComponentTraits.h"


namespace Components {

  template<uint32_t Id, class ...Entities>
  struct Base {
    using Held = std::variant<Entities...>;

    std::vector<std::shared_ptr<Held>>  entities;
    static constexpr const uint32_t     id      { Id };
  };

  struct Drawable       : public Base<0, Entities::Line, Entities::Map> {};
  struct Initializable  : public Base<1, Entities::Map>                 {};

  using Component     = std::variant<Drawable, Initializable>;
  using ComponentPtr  = std::shared_ptr<Component>;
}