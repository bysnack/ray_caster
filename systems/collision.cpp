#include "collision.h"
#include "../utils/vector.h"
#include "../components/components.h"


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
    utils::vector<float> heading_to_pos_modifier(components::heading heading) {
        utils::vector<float> modifier{ 0.f, 0.f };
        switch (heading) {
        case components::heading::east:
            modifier = { -1.f, 0.f };
            break;
        case components::heading::west:
            modifier = { 1.f, 0.f };
            break;
        case components::heading::south:
            modifier = { 0.f, -1.f };
            break;
        case components::heading::north:
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
    template<class entity_t>
    bool detect_collision(const entities::entities::value_type<entities::cell>& cells, const entity_t& entity) {
        components::position user_position{ entity.position - (entity.dimensions / 2) };
        for (auto&& cell : cells) {
            if (user_position.x < cell.second.position.x + cell.second.dimensions.x
                && user_position.x + entity.dimensions.x > cell.second.position.x
                && user_position.y < cell.second.position.y + cell.second.dimensions.y
                && user_position.y + entity.dimensions.y > cell.second.position.y) {
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
    void collision(entities::entities& entities) noexcept {
        // only movables can collisionate
        entities.apply_to<entities::movable>([&](auto&& entity) {
            // detect collisions with map cells
            if (detect_collision(entities.get<entities::cell>(), entity)) {
                // step back if a collision was detected
                entity.position += heading_to_pos_modifier(entity.heading) * entity.speed;
            }
        });
    }
}
