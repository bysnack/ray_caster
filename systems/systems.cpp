#include "systems.h"
#include "initialize_map.h"

namespace systems {
    systems::systems(std::shared_ptr<sf::RenderWindow> render) :
        _systems{ std::make_tuple(std::move(render), &movement, &collision) }
    {
        // initialize one player
        _entities.insert_or_replace(entities::player{}, 0);

        // initialize map cells
        initialize_map(_entities);
    }
}
