#pragma once

#include "traits.h"
#include <unordered_map>

#include "player.h"
#include "cell.h"

namespace entities {

    class entities {
    public:
        template<class entitiy_t>
        using value_type    = std::unordered_map<uint64_t, std::remove_cv_t<std::remove_reference_t<entitiy_t>>>;
        using container     = std::tuple<value_type<cell>, value_type<player>>;

        template<class entitiy_t>
        void insert_or_replace(entitiy_t&& component, uint64_t identifier) {
            std::get<value_type<entitiy_t>>(_entities)[identifier] = component;
        }

        template<template<class entitiy_t> class trait_t, class handler_t>
        void apply_if(handler_t&& handler) {
            // for each entity container
            for_each([handler = std::forward<handler_t>(handler), this](auto&& entities) {
                // get the mapped type
                using mapped_type = typename std::remove_reference_t<decltype(entities)>::mapped_type;
                // only run if needed
                if constexpr (trait_t<mapped_type>::value) {
                    // loop through all the elements of the tuple element
                    for (auto&& entity : entities) {
                        handler(entity.second);
                    }
                }
            });
        }

        template<class handler_t>
        void for_each(handler_t&& handler) {
            // apply handler to each entity in the tuple
            std::apply([handler = std::forward<handler_t>(handler), this](auto&& ...entity) {
                (handler(entity), ...);
            }, _entities);
        }

        template<class entitiy_t>
        decltype(auto) get() {
            return std::get<value_type<entitiy_t>>(_entities);
        }

    private:
        container _entities;
    };
}
