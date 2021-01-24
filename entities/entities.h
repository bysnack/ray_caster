#pragma once

#include "traits.h"
#include <unordered_map>
#include <variant>

#include "player.h"
#include "cell.h"
#include "map.h"
#include "ray.h"

namespace entities {
    template<typename target_t, typename tuple_t>
    struct has_component;

    template<typename target_t, typename ...components_t>
    struct has_component<target_t, std::tuple<components_t...>> : std::disjunction<std::is_same<target_t, components_t>...> {};

    class entities {
    public:
        using container     = std::unordered_map<
            uint32_t,
            std::variant<player, map, cell>
        >;

        template<class entitiy_t>
        void insert_or_replace(entitiy_t&& entity) {
            _entities[_entities.size()] = std::move(entity);
        }

        template<class ...component_t, typename handler_t>
        void apply_for(handler_t handler) {
            // for each variant of entities
            for (auto& [id, entity] : _entities) {
                // visit it and apply the handler
                std::visit([handler = std::move(handler)](auto& element){
                    // first retrieve the entity type so we can verify that the handler
                    // needs to be applied to this entity
                    using entity_t = std::remove_reference_t<decltype(element)>;
                    if constexpr ((has_component<component_t, entity_t>::value && ... && true)) {
                        // components are part of the entity, apply handler
                        handler(element);
                    }
                }, entity);
            }
        }

        template<class entity_t>
        std::vector<entity_t> get() {
            std::vector<entity_t> retval;

            for (auto& [id, entity_variant] : _entities) {
                std::visit([&retval](auto& entity) {
                    if constexpr (std::is_same_v<std::remove_reference_t<decltype(entity)>, entity_t>) {
                        retval.push_back(entity);
                    }
                }, entity_variant);
            }

            return retval;
        }

    private:
        container _entities;
    };
}
