#pragma once

#include <SFML/Graphics.hpp>
#include "../utils/vector.h"
#include "../utils/utilities.h"
#include "../components/components.h"


namespace systems {
    void movement(components::container& container) noexcept;
}