#include <math.h>
#include "render.h"
#include "../entities/entities.h"

namespace {

    components::render calculate_player_render(const entities::player& player)
    {
        const auto& [position, dimensions] = std::get<components::spatial>(player);
        auto screen_dimentions = static_cast<utils::coordinates::screen>(dimensions);
        auto segments = static_cast<size_t>(screen_dimentions.x);
        auto radius = static_cast<size_t>(screen_dimentions.y / 2);

        std::vector<sf::Vertex> vertices;
        vertices.reserve(segments);
        for (size_t i = 0; i < segments; ++i) {
            float theta = 2.f * static_cast<float>(M_PI) * static_cast<float>(i) / static_cast<float>(segments);
            utils::vector<float> vertexPos{
              radius * cosf(theta),
              radius * sinf(theta)
            };
            vertices.emplace_back(vertexPos + static_cast<utils::coordinates::screen>(position), sf::Color::Green);
        }
        return { sf::TriangleFan, std::move(vertices), {} };
    }
}

namespace systems {

    void render(entities::entities& container, sf::RenderWindow& window) {
        window.clear(sf::Color::Black);
        // apply only to renderizable entities
        container.apply_for<components::render>([&](auto&& entity) {
            auto& render = std::get<components::render>(entity);
            // render lights
            if constexpr (entities::has_component<components::light, std::remove_reference_t<decltype(entity)>>::value) {
                const auto& [type, vertices, state] = std::get<components::light>(entity).render;
                window.draw(vertices.data(), vertices.size(), type, state);
            }

            // render player
            if constexpr (entities::is_entity_v<decltype(entity), entities::player>) {
                render = calculate_player_render(entity);
            }

            const auto& [type, vertices, state] = render;
            window.draw(vertices.data(), vertices.size(), type, state);
        });

        window.display();
    }
}