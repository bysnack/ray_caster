#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "../entities/entities.h"


namespace systems {

    class render {
    public:
        render(std::shared_ptr<sf::RenderWindow> window);
        void operator()(entities::container& container) noexcept;

    private:
        std::shared_ptr<sf::RenderWindow> _window;
    };
}