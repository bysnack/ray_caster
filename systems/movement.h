#pragma once

#include <SFML/Graphics.hpp>
#include "../utils/vector.h"
#include "../utils/utilities.h"
#include "../entities/entities.h"


namespace systems {

    class movement {
    public:
        movement(entities::entities& container) noexcept;
        void operator()() noexcept;
    private:
        entities::entities& _entities;
    };
}