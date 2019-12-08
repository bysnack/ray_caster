#include "collision.h"
#include "../utils/vector.h"

/*
*   Anonymous namespace
*
*   @brief  Contains a set of helper functions used to detect collisions
*/
namespace {
    /*
    *   Heading to pos modifier
    *
    *   @brief              Calculates a position modifier depending on the current heading
    *   @param  heading     The heading entity of the movable component 
    *   @returns            The calculated position modifier
    */
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

    /*
    *   Cells colision detecter
    *
    *   @brief              Detects collisions between a movable and a group of cells
    *   @param  cells       The group of cells
    *   @param  component   The component to detect collisions with
    *   @returns            Whether a collision was detected or not
    */
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
    /*
    *   Collisions system functor
    *
    *   @brief              Handles collisions
    *   @param  container   The container of all components
    */
    void collision(components::container& container) noexcept {
        // only movables can collisionate
        container.apply_if<components::is_movable>([&](auto&& elem) {
            // detect collisions with map cells
            if (detect_collision(container.get<components::cell>(), elem)) {
                // step back if a collision was detected
                elem.position += heading_to_pos_modifier(elem.heading) * elem.speed;
            }
        });
    }
}
