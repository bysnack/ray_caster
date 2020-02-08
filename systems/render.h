#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "../entities/entities.h"


namespace systems {

    class render {
    public:
        render(entities::entities& container, std::shared_ptr<sf::RenderWindow> window);
        void operator()() noexcept;

    private:
        std::shared_ptr<sf::RenderWindow> _window;
        entities::entities& _entities;
    };
}