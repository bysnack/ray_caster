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
    utils::coordinates::world heading_to_pos_modifier(components::heading heading) {
        utils::coordinates::world modifier{ 0.f, 0.f };
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
        auto [ecx, ecy] = entity.position - (entity.dimensions / 2);
        for (auto&& cell : cells) {
            const auto& [cx, cy] = cell.second.position;
            if (ecx < cx + cell.second.dimensions.x
                && ecx + entity.dimensions.x > cx
                && ecy < cy + cell.second.dimensions.y
                && ecy + entity.dimensions.y > cy) {
                return true;
            }
        }
        return false;
    }
}

namespace systems {
    collision::collision(entities::entities& container) noexcept :
        _entities{ container }
    {}

    /*
    *   Collisions system functor
    *
    *   @brief              Handles collisions
    *   @param  container   The container of all components
    */
    void collision::operator()() noexcept {
        // only movables can collisionate
        _entities.apply_to<entities::movable>([&](auto&& entity) {
            // detect collisions with map cells
            if (detect_collision(_entities.get<entities::cell>(), entity)) {
                // step back if a collision was detected
                entity.position += heading_to_pos_modifier(entity.heading) * entity.speed;
            }
        });
    }
}
