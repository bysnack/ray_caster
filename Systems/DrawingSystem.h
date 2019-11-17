#pragma once

#include <gsl/span>
#include <variant>
#include <iostream>
#include "../Components/Components.h"

class DrawingSystem {
  public:
    DrawingSystem(std::shared_ptr<sf::RenderWindow> window) :
      _window{ std::move(window) }
    {}
     
    template<class Component>
    void run(Component&& components) {
      // start drawing
      _window->clear(sf::Color::Black);
      components.template apply<Components::Drawable>([&](auto&& elem){
        for (const auto& [type, vertices] : elem.render) {
          _window->draw(vertices.data(), vertices.size(), type);
        }
      });
      _window->display();
    }

  private:
    std::shared_ptr<sf::RenderWindow> _window;
};