#include "lights.h"
#include "../config.h"
#include "../utils/utilities.h"
#include "../utils/coordinates/coordinates.h"
#include "../entities/entities.h"

#ifdef _WIN32
#define _USE_MATH_DEFINES // for C++
#endif
#include <math.h>

namespace {

	bool isInBounds(const utils::coordinates::screen& position) noexcept {
		auto [x, y] = static_cast<utils::coordinates::tile>(position);

		if (x > config::MAP_SIZE.first || y > config::MAP_SIZE.second) {
			return false;
		}
		if (x < 0.f || y < 0.f) {
			return false;
		}
		return true;
	}

	bool isColiding(const utils::coordinates::tile& target, const entities::entities::value_type<entities::map>& map) noexcept {
		for (const auto& elem : map) {
			const auto& [x, y] = target;
			int calc = x + y * config::MAP_SIZE.first;
			
			return elem.second.seed[calc] == 1;
		}

		return false;
	}

	utils::coordinates::world calculate_horizontal_intersection(const utils::coordinates::world& position, float angle, const entities::entities::value_type<entities::map>& map) {
		float tan = tanf(angle);
		float sin = sinf(angle);
		float cos = cosf(angle);

		// no intersection
		if (utils::cmpf(sin, 0.f)) {
			return {
				std::numeric_limits<float>::lowest(),
				std::numeric_limits<float>::lowest()
			};
		}

		// calculate the horizontal step positions
		utils::coordinates::world coordinates{
			std::round(cos),
			std::round(sin)
		};

		if (!utils::cmpf(cos, 0.f)) {
			coordinates.x = copysignf(1.f, cos) / std::abs(tan);
			coordinates.y = copysignf(1.f, sin);
		}
		auto step = coordinates;

		// calculate the position from the start point to the grid
		auto [pX, pY] = position;
		if (sin > 0.f) {
			coordinates.y = ceilf(pY) - pY + 0.0001f;
		}
		else {
			coordinates.y = floorf(pY) - pY - 0.0001f;
		}

		if (utils::cmpf(cos, 0.f)) {
			coordinates.x = 0.f;
		}
		else {
			coordinates.x = coordinates.y / tan;
		}
		auto diff = coordinates;

		// calculate intersection
		utils::coordinates::world intersection{ position.x + diff.x, position.y + diff.y };

		while (isInBounds(intersection) && !isColiding(intersection, map)) {
			intersection += { step.x, step.y};
		}

		return intersection;
	}

	utils::coordinates::screen calculate_vertical_intersection(const utils::coordinates::world& position, float angle, const entities::entities::value_type<entities::map>& map) {
		float tan = tanf(angle);
		float sin = sinf(angle);
		float cos = cosf(angle);

		// no intersection
		if (utils::cmpf(cos, 0.f)) {
			return {
				std::numeric_limits<float>::lowest(),
				std::numeric_limits<float>::lowest()
			};
		}

		// calculate the vertical step positions
		utils::coordinates::world coordinates{
			std::round(cos),
			std::round(sin)
		};

		if (!utils::cmpf(sin, 0.f)) {
			coordinates.x = copysignf(1.f, cos);
			coordinates.y = copysignf(1.f, sin) * std::abs(tan);
		}
		auto step = coordinates;

		// calculate the position from the start point to the grid
		auto [pX, pY] = static_cast<utils::coordinates::world>(position);
		if (cos > 0.f) {
			coordinates.x = ceilf(pX) - pX + 0.0001f;
		}
		else {
			coordinates.x = floorf(pX) - pX - 0.0001f;
		}

		if (utils::cmpf(sin, 0.f)) {
			coordinates.y = 0.f;
		}
		else {
			coordinates.y = coordinates.x * tan;
		}
		auto diff = coordinates;

		// calculate intersection
		utils::coordinates::world intersection{ position.x + diff.x, position.y + diff.y };

		while (isInBounds(intersection) && !isColiding(intersection, map)) {
			intersection += { step.x, step.y};
		}

		return intersection;
	}

	std::tuple<utils::coordinates::world, utils::coordinates::world> calculate_intersections(const utils::coordinates::world& position, float angle, const entities::entities::value_type<entities::map>& map) {
		return {
			calculate_horizontal_intersection(position, angle, map),
			calculate_vertical_intersection(position, angle, map),
		};
	}
}

namespace systems {
	constexpr size_t rays_amount = 1000;

	lights::lights(entities::entities& container) noexcept :
		_entities{ container }
	{
	}

	void lights::operator()() noexcept {
		_entities.apply_to<entities::casteable>([&](auto&& entity) {
			auto& [primitive, vertices, state] = entity.light.render;
			// add the rays
			float angle = 2.f * M_PI;
			float modifier = angle / rays_amount;

			auto scale = [&](const utils::coordinates::screen& inter, const utils::coordinates::screen& pos, const utils::coordinates::screen& dim)->utils::coordinates::screen {
				auto [sx, sy] = entity.light.texture->getSize();
				return {
					(sx / dim.x) * (inter.x - pos.x + dim.x / 2.f),
					(sy / dim.y) * (inter.y - pos.y + dim.y / 2.f)
				};
			};

			vertices.clear();
			primitive = sf::TriangleFan;

			if (!entity.light.texture) {
				entity.light.texture = std::make_unique<sf::Texture>();
				if (entity.light.texture->loadFromFile("assets/light.png")) {
					state.texture = entity.light.texture.get();
				}
			};

			// first vertex in the center
			vertices.emplace_back(static_cast<utils::coordinates::screen>(entity.position), scale(entity.position, entity.position, entity.light.dimensions));

			// calculate the next rays
			for (auto i = 0u; i < rays_amount; i++) {
				// calculate intersections
				auto [interX, interY] = calculate_intersections(entity.position, angle, _entities.get<entities::map>());
				auto inter = utils::distance(entity.position, interX) <= utils::distance(entity.position, interY) ?
					static_cast<utils::coordinates::screen>(interX) :
					static_cast<utils::coordinates::screen>(interY);

				vertices.emplace_back(inter, scale(inter, entity.position, entity.light.dimensions));
				angle += modifier;

			}
			vertices.emplace_back(vertices[1].position, scale(vertices[1].position, entity.position, entity.light.dimensions));
		});
	}
}
