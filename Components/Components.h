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

    std::vector<Held>  entities;
    static constexpr const uint32_t     id      { Id };
  };

  struct Drawable       : public Base<0, std::shared_ptr<Entities::Line>, std::shared_ptr<Entities::Map>> {};
  struct Initializable  : public Base<1, std::shared_ptr<Entities::Map>>                                  {};

  using Component     = std::variant<Drawable, Initializable>;
  using ComponentPtr  = std::shared_ptr<Component>;
}