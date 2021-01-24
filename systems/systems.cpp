#include <functional>

#include "systems.h"
#include "initialize_map.h"


namespace systems {

    systems::systems(entities::entities& container)
    {
        // initialize one player
        entities::player player{};
        std::get<components::speed>(player) = 0.25f;
        container.insert_or_replace(std::move(player));

        // initialize map cells
        initialize_map(container);
    }
}
