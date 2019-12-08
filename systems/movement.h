#pragma once

#include <SFML/Graphics.hpp>
#include "../utils/vector.h"
#include "../utils/utilities.h"
#include "../entities/entities.h"


namespace systems {
    void movement(entities::container& container) noexcept;
}