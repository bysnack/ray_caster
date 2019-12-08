#pragma once

#include <type_traits>
#include <tuple>
#include "../entities/entities.h"

namespace components {

 // template<class Target, class Comp>
  //struct belongsToComponent;

 // template<class Target, class ...Alts>
 //struct belongsToComponent<Target, Component<Alts...>> : public std::disjunction<std::is_same<Target, Alts>...> {};

  template<class component_t, class = void>
  struct is_renderizable : public std::false_type{};

  template<class component_t>
  struct is_renderizable<component_t, std::enable_if_t<
    // render entity present
    std::is_same_v<decltype(std::remove_cv_t<std::remove_reference_t<component_t>>::render), entities::render>
  >> : public std::true_type{};

  template<class component_t, class = void>
  struct is_movable : public std::false_type{};

  template<class component_t>
  struct is_movable<component_t, std::void_t<
    // speed entity present
    std::is_same<decltype(std::remove_cv_t<std::remove_reference_t<component_t>>::speed), entities::speed>,
    // position entity present
    std::is_same<decltype(std::remove_cv_t<std::remove_reference_t<component_t>>::position), entities::position>,
    // heading entity present
    std::is_same<decltype(std::remove_cv_t<std::remove_reference_t<component_t>>::heading), entities::heading>
  >> : public std::true_type{};

  template<class component_t, class = void>
  struct is_collisionable : public std::false_type{};

  template<class component_t>
  struct is_collisionable<component_t, std::enable_if_t<
    // position entity present
    std::is_same_v<decltype(std::remove_cv_t<std::remove_reference_t<component_t>>::position), entities::position>
  >> : public std::true_type{};

  template<class component_t>
  struct true_trait : std::true_type{};

  template<class component_t>
  constexpr bool is_renderizable_v = is_renderizable<component_t>::value;

  template<class target_t, class component_t>
  constexpr bool is_component_v = std::is_same_v<std::remove_cv_t<std::remove_reference_t<target_t>>, component_t>;
}
