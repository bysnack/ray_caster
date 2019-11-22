#pragma once

#include <gsl/span>
#include <variant>
#include <iostream>
#include "../components/components.h"

namespace systems {

  class render {
    public:
      render(std::shared_ptr<sf::RenderWindow> window) :
        _window{ std::move(window) }
      {}
      
      void operator()(components::container& container) {
        _window->clear(sf::Color::Black);
        // render user in the right position

        container.apply_if<components::is_renderizable>([&](auto&& component) {
          if constexpr (components::is_component_v<decltype(component), components::player>) {
            component.render = renderUser(component.position);
          }
          const auto& [type, vertices] = component.render;
          _window->draw(vertices.data(), vertices.size(), type);
        });

        _window->display();
      }

    private:
      entities::render renderUser(const utils::vector<float>& position)
      {
        static constexpr const size_t segments{ 10  };
        static constexpr const size_t radius  { 5   };

        std::vector<sf::Vertex> vertices;
        vertices.reserve(segments);
        for (size_t i = 0; i < segments; ++i) {
          float theta = 2.f * M_PI * static_cast<float>(i) / static_cast<float>(segments);
          utils::vector<float> vertexPos{
            radius * cosf(theta),
            radius * sinf(theta)
          };
          vertices.emplace_back(vertexPos + position, sf::Color::Green);
        }
        return { sf::TriangleFan, std::move(vertices) };
      }

    private:
      std::shared_ptr<sf::RenderWindow> _window;
  };
}