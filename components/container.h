#pragma once

#include "traits.h"
#include <unordered_map>

#include "player.h"
#include "cell.h"

namespace components {

  class container {
    public:
      template<class component_t>
      using components      = std::unordered_map<uint64_t, std::remove_cv_t<std::remove_reference_t<component_t>>>;
      using underlying_type = std::tuple<components<cell>, components<player>>;

      template<class component_t>
      void insert_or_replace(component_t&& component, uint64_t identifier) {
        std::get<components<component_t>>(_components)[identifier] = component;
      }

      template<template<class component_t> class trait_t, class handler_t, size_t index = 0>
      void apply_if(handler_t&& handler) {
        using mapped_type = typename std::tuple_element_t<index, underlying_type>::mapped_type;
        if constexpr (trait_t<mapped_type>::value) {
          // loop through all the elements of the tuple element
          for (auto&& element : std::get<index>(_components)) {
            handler(element.second);
          }
        }

        // next tuple element
        if constexpr (index < std::tuple_size_v<underlying_type> - 1) {
          apply_if<trait_t, handler_t, index + 1>(std::forward<handler_t>(handler));
        }
      }

      template<class component_t>
      decltype(auto) get() {
        return std::get<components<component_t>>(_components);
      }
    private:
      underlying_type _components;
  };
}
