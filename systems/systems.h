#pragma once

#include <memory>

#include "collision.h"
#include "movement.h"
#include "render.h"
#include "../entities/entities.h"
//#include "ray_caster.h"


namespace systems {

    class systems {
    public:
        using systems_t = std::tuple<render, movement, collision>;

        systems(std::shared_ptr<sf::RenderWindow> window);

        void run_all() {
            std::apply([](auto&& ...system) {
                (system(), ...);
            }, _systems);
        }

    private:
        entities::entities  _entities;
        systems_t           _systems;
    };
}
