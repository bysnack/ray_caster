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

}