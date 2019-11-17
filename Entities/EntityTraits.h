#pragma once

#include <type_traits>

namespace Entities {
  /**
   *  @brief  Is entity initializable type trait
   */
  template<class Target, class = void>
  struct is_initializable : std::false_type{};

  template<class Target>
  struct is_initializable<Target, std::enable_if_t<
    // only certan specific types are initializables
    std::is_same_v<Target, Map>

  >> : std::true_type{};

  template<class Target>
  static constexpr const bool is_initializable_v = is_initializable<Target>::value;

  /**
   *  @brief  Is entity renderizable type trait
   */
  template<class Target, class = void>
  struct is_renderizable : std::false_type{};

  template<class Target>
  struct is_renderizable<Target, std::enable_if_t<
    // property render data exists
    std::is_same_v<decltype(Target::render), Properties::RenderData>

  >> : std::true_type{};

  template<class Target>
  static constexpr const bool is_renderizable_v = is_renderizable<Target>::value;
}
