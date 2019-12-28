#include <functional>

#include "systems.h"
#include "initialize_map.h"


namespace systems {
    systems::systems(std::shared_ptr<sf::RenderWindow> window) :
        _entities{},
        _systems{ { _entities, std::move(window) },  _entities, _entities }
    {
        // initialize one player
        _entities.insert_or_replace(entities::player{}, 0);

        // initialize map cells
        initialize_map(_entities);
    }
}
