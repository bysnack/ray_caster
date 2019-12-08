#pragma once


#include "../components/components.h"


namespace systems {
    using tile = std::vector<sf::Vertex>;
    /*
    *   Map initializer
    *
    *   @brief              Initializes the cells of a map
    *   @param  container   The component container where to store the cells
    */
    void initialize_map(components::container& container);
}