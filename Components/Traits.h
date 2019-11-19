#pragma once

#include <type_traits>

#include "../Entities/Entities.h"
#include "Components.h"

namespace Components {

  template<class Target, class Comp>
  struct belongsToComponent;

  template<class Target, class ...Alts>
  struct belongsToComponent<Target, Component<Alts...>> : public std::disjunction<std::is_same<Target, Alts>...> {
    using Component = Component<Alts...>;
  };
}