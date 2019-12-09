#pragma once

#include <memory>

#include "collision.h"
#include "movement.h"
#include "render.h"
#include "../entities/entities.h"


namespace systems {

    class systems {
    public:
        using systems_t = std::tuple<render, decltype(&movement), decltype(&collision)>;

        systems(std::shared_ptr<sf::RenderWindow> render);

        void run_all() {
            for_each([this](auto&& system){
                system(_entities);
            });
        }

        template<class handler_t, size_t index = 0>
        void for_each(handler_t&& handler) {
            // invoke the handler for the specific system
            handler(std::get<index>(_systems));

            // try to invoke the next one
            if constexpr (index < std::tuple_size_v<systems_t> -1) {
                for_each<handler_t, index + 1>(std::forward<handler_t>(handler));
            }
        }
    private:
        systems_t           _systems;
        entities::entities  _entities{};
    };
}
