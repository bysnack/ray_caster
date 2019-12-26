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
            std::apply([this](auto&& ...system) {
                (system(_entities), ...);
            }, _systems);
        }

    private:
        systems_t           _systems;
        entities::entities  _entities{};
    };
}
