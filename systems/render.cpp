#pragma once

#ifdef _WIN32
#define _USE_MATH_DEFINES // for C++
#endif
#include <math.h>

#include "render.h"

namespace {

    components::render calculate_player_render(const entities::player& player)
    {
        auto segments = static_cast<size_t>(player.dimensions.x);
        auto radius = static_cast<size_t>(player.dimensions.y / 2);

        std::vector<sf::Vertex> vertices;
        vertices.reserve(segments);
        for (size_t i = 0; i < segments; ++i) {
            float theta = 2.f * static_cast<float>(M_PI) * static_cast<float>(i) / static_cast<float>(segments);
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

    render::render(std::shared_ptr<sf::RenderWindow> window) :
        _window{ std::move(window) }
    {}

    void render::operator()(entities::entities& entities) noexcept {
        _window->clear(sf::Color::Black);
        // apply only to renderizable entities
        entities.apply_if<entities::is_renderizable>([&](auto&& entity) {
            // render player
            if constexpr (entities::is_entity_v<decltype(entity), entities::player>) {
                entity.render = calculate_player_render(entity);
            }
            const auto& [type, vertices] = entity.render;
            _window->draw(vertices.data(), vertices.size(), type);
            });

        _window->display();
    }
}