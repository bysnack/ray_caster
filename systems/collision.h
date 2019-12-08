#pragma once

#include "../components/components.h"


namespace systems {
    /*
    *   Collision system.
    *
    *   @brief  Handles collisions for movable components 
    */
    void collision(components::container& container) noexcept;
}
