#pragma once

#include <memory>

#include "collision.h"
#include "movement.h"
#include "ray_cast.h"
#include "render.h"
#include "../components/container.h"


namespace systems {

    class systems {
    public:
        using systems_t = std::tuple<render, decltype(&movement), decltype(&collision)>;

        systems(std::shared_ptr<sf::RenderWindow> render);

        template<int index = 0>
        void run_all() {
            // run the system with the components
            std::get<index>(_systems)(_components);
            // try the next one
            if constexpr (index + 1 < std::tuple_size_v<systems_t>) {
                run_all<index + 1>();
            }
        }
    private:
        systems_t               _systems;
        components::container   _components{};
    };
}
