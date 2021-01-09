#include <math.h>
#include "render.h"

namespace {

    components::render calculate_player_render(const entities::player& player)
    {
        auto screen_dimentions = static_cast<utils::coordinates::screen>(player.dimensions);
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
            vertices.emplace_back(vertexPos + static_cast<utils::coordinates::screen>(player.position), sf::Color::Green);
        }
        return { sf::TriangleFan, std::move(vertices), {} };
    }
}

namespace systems {

    render::render(entities::entities& container, std::shared_ptr<sf::RenderWindow> window) :
        _entities{ container },
        _window{ std::move(window) }
    {}

    void render::operator()() noexcept {
        _window->clear(sf::Color::Black);
        // apply only to renderizable entities
        _entities.apply_to<entities::renderizable>([&](auto&& entity) {
            // render player
            if constexpr (entities::is_entity_v<decltype(entity), entities::player>) {
                entity.render = calculate_player_render(entity);
            }
            const auto& [type, vertices, state] = entity.render;
            _window->draw(vertices.data(), vertices.size(), type, state);
            });

        _window->display();
    }
}