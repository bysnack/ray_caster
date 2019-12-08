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
    
    template<class component_t>
    bool detect_collision(const components::container::components<components::cell>& cells, const component_t& component) {
        entities::position user_position{ component.position - (component.dimensions / 2) };
        for (auto&& cell : cells) {
            if (user_position.x < cell.second.position.x + cell.second.dimensions.x
                && user_position.x + component.dimensions.x > cell.second.position.x
                && user_position.y < cell.second.position.y + cell.second.dimensions.y
                && user_position.y + component.dimensions.y > cell.second.position.y) {
                return true;
            }
        }
        return false;
    }
}

namespace systems {
    class collision {
    public:
        void operator()(components::container& container) {
            // only movables can collisionate
            container.apply_if<components::is_movable>([&](auto&& elem) {
                if (detect_collision(container.get<components::cell>(), elem)) {
                    elem.position += heading_to_pos_modifier(elem.heading) * elem.speed;
                }
            });
        }
    };
}
