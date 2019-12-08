#pragma once

#include "traits.h"
#include <unordered_map>

#include "player.h"
#include "cell.h"

namespace entities {

    class container {
    public:
        template<class entitiy_t>
        using entities        = std::unordered_map<uint64_t, std::remove_cv_t<std::remove_reference_t<entitiy_t>>>;
        using underlying_type = std::tuple<entities<cell>, entities<player>>;

        template<class entitiy_t>
        void insert_or_replace(entitiy_t&& component, uint64_t identifier) {
            std::get<entities<entitiy_t>>(_entities)[identifier] = component;
        }

        template<template<class entitiy_t> class trait_t, class handler_t, size_t index = 0>
        void apply_if(handler_t&& handler) {
            using mapped_type = typename std::tuple_element_t<index, underlying_type>::mapped_type;
            if constexpr (trait_t<mapped_type>::value) {
                // loop through all the elements of the tuple element
                for (auto&& element : std::get<index>(_entities)) {
                handler(element.second);
                }
            }

            // next tuple element
            if constexpr (index < std::tuple_size_v<underlying_type> - 1) {
                apply_if<trait_t, handler_t, index + 1>(std::forward<handler_t>(handler));
            }
        }

        template<class entitiy_t>
        decltype(auto) get() {
            return std::get<entities<entitiy_t>>(_entities);
        }
    private:
        underlying_type _entities;
    };
}
