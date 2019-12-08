#pragma once

#include "../entities/entities.h"


namespace systems {
    /*
    *   Collision system.
    *
    *   @brief  Handles collisions for movable entities 
    */
    void collision(entities::container& container) noexcept;
}
