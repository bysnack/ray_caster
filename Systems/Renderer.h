#pragma once

#include <gsl/span>
#include <variant>
#include <iostream>
#include "../Components/Components.h"

namespace Systems {

  class Renderer {
    public:
      Renderer(std::shared_ptr<sf::RenderWindow> window) :
        _window{ std::move(window) }
      {}
      
      void run(Components::Container& components) {
        // render user in the right position
        components.template apply<Components::User>([&](auto&& elem){
          for (auto&& renderizable : elem.render) {
            renderizable = renderUser(elem.position);
          }
        });

        // start drawing
        _window->clear(sf::Color::Black);
        components.apply<Components::Drawable>([&](auto&& elem){
          for (const auto& [type, vertices] : elem.render) {
            _window->draw(vertices.data(), vertices.size(), type);
          }
        });
        _window->display();
      }

    private:
      Entities::Properties::Renderizable renderUser(const Utils::Vector<float>& position)
      {
        static constexpr const size_t segments{ 10 };
        static constexpr const size_t radius  { 10 };

        std::vector<sf::Vertex> vertices;
        vertices.reserve(segments);
        for (size_t i = 0; i < segments; ++i) {
          float theta = 2.f * M_PI * static_cast<float>(i) / static_cast<float>(segments);
          Utils::Vector<float> vertexPos{
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