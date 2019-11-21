#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>

#include "../Utils/Vector.h"
#include "../Entities/Properties/RenderData.h"

namespace {
  constexpr const size_t segments{ 10 };
  constexpr const size_t radius  { 10 };
};

namespace Systems {

  class InitUser {
    public:
      template<class Component>
      InitUser(Component&& components)
      {
        components.template apply<Components::User>([](auto&& elem){
          std::vector<sf::Vertex> vertices;

          for (size_t i = 0; i < segments; ++i) {
            float theta = 2.f * M_PI * static_cast<float>(i) / static_cast<float>(segments);
            Utils::Vector<float> vertexPos{
              radius * cosf(theta),
              radius * sinf(theta)
            };
            vertices.emplace_back(vertexPos + elem.position, sf::Color::Green);
          }
          elem.render.push_back({sf::TriangleFan, std::move(vertices)});
        });
      }
  };
}