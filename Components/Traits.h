#pragma once

#include <type_traits>
#include <tuple>

namespace Components {

  template<class Target, class Comp>
  struct belongsToComponent;

  template<class Target, class ...Alts>
  struct belongsToComponent<Target, Component<Alts...>> : public std::disjunction<std::is_same<Target, Alts>...> {};
}
