#pragma once

#include <gsl/span>
#include <variant>
#include <iostream>
#define _USE_MATH_DEFINES // for C++
#include <math.h>
#include "../components/components.h"

namespace {
    entities::render calculate_player_render(const components::player& player)
    {
        auto segments = static_cast<size_t>(player.dimensions.x);
        auto radius   = static_cast<size_t>(player.dimensions.y / 2);

        std::vector<sf::Vertex> vertices;
        vertices.reserve(segments);
        for (size_t i = 0; i < segments; ++i) {
            float theta = 2.f * M_PI * static_cast<float>(i) / static_cast<float>(segments);
            utils::vector<float> vertexPos{
              radius * cosf(theta),
              radius * sinf(theta)
            };
            vertices.emplace_back(vertexPos + player.position, sf::Color::Green);
        }
        return { sf::TriangleFan, std::move(vertices) };
    }
}

namespace systems {

  class render {
    public:
      render(std::shared_ptr<sf::RenderWindow> window) :
        _window{ std::move(window) }
      {}
      
      void operator()(components::container& container) {
        _window->clear(sf::Color::Black);
        // for each renderizable component
        container.apply_if<components::is_renderizable>([&](auto&& component) {
          // render player
          if constexpr (components::is_component_v<decltype(component), components::player>) {
            component.render = calculate_player_render(component);
          }
          const auto& [type, vertices] = component.render;
          _window->draw(vertices.data(), vertices.size(), type);
        });

        _window->display();
      }

    private:
      std::shared_ptr<sf::RenderWindow> _window;
  };
}