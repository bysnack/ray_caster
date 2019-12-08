#pragma once

#include <type_traits>
#include <tuple>
#include "../components/components.h"

namespace entities {

 // template<class Target, class Comp>
  //struct belongsToComponent;

 // template<class Target, class ...Alts>
 //struct belongsToComponent<Target, Component<Alts...>> : public std::disjunction<std::is_same<Target, Alts>...> {};

  template<class entity_t, class = void>
  struct is_renderizable : public std::false_type{};

  template<class entity_t>
  struct is_renderizable<entity_t, std::enable_if_t<
    // render component present
    std::is_same_v<decltype(std::remove_cv_t<std::remove_reference_t<entity_t>>::render), components::render>
  >> : public std::true_type{};

  template<class entity_t, class = void>
  struct is_movable : public std::false_type{};

  template<class entity_t>
  struct is_movable<entity_t, std::void_t<
    // speed component present
    std::is_same<decltype(std::remove_cv_t<std::remove_reference_t<entity_t>>::speed), components::speed>,
    // position component present
    std::is_same<decltype(std::remove_cv_t<std::remove_reference_t<entity_t>>::position), components::position>,
    // heading component present
    std::is_same<decltype(std::remove_cv_t<std::remove_reference_t<entity_t>>::heading), components::heading>
  >> : public std::true_type{};

  template<class entity_t, class = void>
  struct is_collisionable : public std::false_type{};

  template<class entity_t>
  struct is_collisionable<entity_t, std::enable_if_t<
    // position component present
    std::is_same_v<decltype(std::remove_cv_t<std::remove_reference_t<entity_t>>::position), components::position>
  >> : public std::true_type{};

  template<class entity_t>
  struct true_trait : std::true_type{};

  template<class entity_t>
  constexpr bool is_renderizable_v = is_renderizable<entity_t>::value;

  template<class target_t, class entity_t>
  constexpr bool is_entity_v = std::is_same_v<std::remove_cv_t<std::remove_reference_t<target_t>>, entity_t>;
}
