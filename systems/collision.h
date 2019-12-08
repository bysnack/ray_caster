#pragma once

#include "../components/components.h"
#include <optional>
#include "../utils/vector.h"
#include <iostream>

namespace {
    utils::vector<float> heading_to_pos_modifier(entities::heading heading) {
        utils::vector<float> modifier{ 0.f, 0.f };
        switch (heading) {
        case entities::heading::east:
            modifier = { -1.f, 0.f };
            break;
        case entities::heading::west:
            modifier = { 1.f, 0.f };
            break;
        case entities::heading::south:
            modifier = { 0.f, -1.f };
            break;
        case entities::heading::north:
            modifier = { 0.f, 1.f };
            break;
        }
        return modifier;
    }
}

namespace systems {
    class collision {
    public:
        void operator()(components::container& container) {
            // only movables can collisionate
            container.apply_if<components::is_movable>([&](auto&& elem) {
                if (detectCollision(container.get<components::cell>(), elem.position)) {
                    elem.position += heading_to_pos_modifier(elem.heading) * elem.speed;
                }
            });
        }

    private:
        bool detectCollision(const components::container::components<components::cell>& cells, const entities::position& position) {
            for (auto&& cell : cells) {
                if (position.x < cell.second.position.x + cell.second.dimensions.x
                    && position.x + cell.second.dimensions.x > cell.second.position.x
                    && position.y < cell.second.position.y + cell.second.dimensions.y
                    && position.y + cell.second.dimensions.y > cell.second.position.y) {
                    return true;
                }
            }
            return false;
        }
    };
}
