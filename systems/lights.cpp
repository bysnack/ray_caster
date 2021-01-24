#include "lights.h"
#include "../config.h"
#include "../entities/entities.h"
#include "../utils/coordinates/coordinates.h"
#include "../utils/utilities.h"

#include <math.h>

namespace {

bool isInBounds(const utils::coordinates::screen &position) noexcept {
  auto [x, y] = static_cast<utils::coordinates::tile>(position);

  if (x > config::MAP_SIZE.first || y > config::MAP_SIZE.second) {
    return false;
  }
  if (x < 0.f || y < 0.f) {
    return false;
  }
  return true;
}

bool isColiding(const utils::coordinates::tile &target,
                const std::vector<entities::map> &map) noexcept {
  for (const auto &elem : map) {
    const auto &[x, y] = target;
    int calc = x + y * config::MAP_SIZE.first;

    return std::get<components::seed>(elem)[calc] == 1;
  }

  return false;
}

utils::coordinates::world
calculate_horizontal_intersection(const utils::coordinates::world &position,
                                  float angle, float reach,
                                  const std::vector<entities::map> &map) {
  float tan = tanf(angle);
  float sin = sinf(angle);
  float cos = cosf(angle);

  // no intersection
  if (utils::cmpf(sin, 0.f)) {
    return {std::numeric_limits<float>::lowest(),
            std::numeric_limits<float>::lowest()};
  }

  // calculate the horizontal step positions
  utils::coordinates::world coordinates{std::round(cos), std::round(sin)};

  if (!utils::cmpf(cos, 0.f)) {
    coordinates.x = copysignf(1.f, cos) / std::abs(tan);
    coordinates.y = copysignf(1.f, sin);
  }
  auto step = coordinates;

  // calculate the position from the start point to the grid
  auto [pX, pY] = position;
  if (sin > 0.f) {
    coordinates.y = ceilf(pY) - pY + 0.0001f;
  } else {
    coordinates.y = floorf(pY) - pY - 0.0001f;
  }

  if (utils::cmpf(cos, 0.f)) {
    coordinates.x = 0.f;
  } else {
    coordinates.x = coordinates.y / tan;
  }
  auto diff = coordinates;

  // calculate intersection
  utils::coordinates::world intersection{position.x + diff.x,
                                         position.y + diff.y};
  float squared_distance = utils::squared_distance(position, intersection);

  while (squared_distance <= reach * reach && isInBounds(intersection) &&
         !isColiding(intersection, map)) {
    intersection += {step.x, step.y};
    squared_distance = utils::squared_distance(position, intersection);
  }

  return intersection;
}

utils::coordinates::screen
calculate_vertical_intersection(const utils::coordinates::world &position,
                                float angle, float reach,
                                const std::vector<entities::map> &map) {
  float tan = tanf(angle);
  float sin = sinf(angle);
  float cos = cosf(angle);

  // no intersection
  if (utils::cmpf(cos, 0.f)) {
    return {std::numeric_limits<float>::lowest(),
            std::numeric_limits<float>::lowest()};
  }

  // calculate the vertical step positions
  utils::coordinates::world coordinates{std::round(cos), std::round(sin)};

  if (!utils::cmpf(sin, 0.f)) {
    coordinates.x = copysignf(1.f, cos);
    coordinates.y = copysignf(1.f, sin) * std::abs(tan);
  }
  auto step = coordinates;

  // calculate the position from the start point to the grid
  auto [pX, pY] = static_cast<utils::coordinates::world>(position);
  if (cos > 0.f) {
    coordinates.x = ceilf(pX) - pX + 0.0001f;
  } else {
    coordinates.x = floorf(pX) - pX - 0.0001f;
  }

  if (utils::cmpf(sin, 0.f)) {
    coordinates.y = 0.f;
  } else {
    coordinates.y = coordinates.x * tan;
  }
  auto diff = coordinates;

  // calculate intersection
  utils::coordinates::world intersection{position.x + diff.x,
                                         position.y + diff.y};

  while (isInBounds(intersection) && !isColiding(intersection, map)) {
    intersection += {step.x, step.y};
  }

  return intersection;
}

std::tuple<utils::coordinates::world, utils::coordinates::world>
calculate_intersections(const utils::coordinates::world &position, float angle,
                        float reach, const std::vector<entities::map> &map) {
  return {
      calculate_horizontal_intersection(position, angle, reach, map),
      calculate_vertical_intersection(position, angle, reach, map),
  };
}
} // namespace

namespace systems {
constexpr size_t rays_amount = 300;

void lights(entities::entities &container) noexcept {
  container.apply_for<components::light>([&](auto &&entity) {
    auto &light = std::get<components::light>(entity);
    auto &[position, dimensions] = std::get<components::spatial>(entity);
    auto &[primitive, vertices, state] = light.render;
    // add the rays
    float angle = 2.f * M_PI;
    float modifier = angle / rays_amount;

    auto scale = [&](const utils::coordinates::screen &inter,
                     const utils::coordinates::screen &pos,
                     const utils::coordinates::screen &dim)
        -> utils::coordinates::screen {
      auto [sx, sy] = light.texture->getSize();
      return {(sx / dim.x) * (inter.x - pos.x + dim.x / 2.f),
              (sy / dim.y) * (inter.y - pos.y + dim.y / 2.f)};
    };

    vertices.clear();
    primitive = sf::TriangleFan;

    if (!light.texture) {
      light.texture = std::make_unique<sf::Texture>();
      if (light.texture->loadFromFile("assets/light.png")) {
        state.texture = light.texture.get();
      }
    };

    // first vertex in the center
    vertices.emplace_back(static_cast<utils::coordinates::screen>(position),
                          scale(position, position, light.dimensions));

    // calculate the next rays
    for (auto i = 0u; i < rays_amount; i++) {
      // calculate intersections
      auto [interX, interY] =
          calculate_intersections(position, angle, light.dimensions.x / 2,
                                  container.get<entities::map>());
      auto inter = utils::is_closer(position, interX, interY)
                       ? static_cast<utils::coordinates::screen>(interX)
                       : static_cast<utils::coordinates::screen>(interY);

      vertices.emplace_back(inter, scale(inter, position, light.dimensions));
      angle += modifier;
    }
    vertices.emplace_back(
        vertices[1].position,
        scale(vertices[1].position, position, light.dimensions));
  });
}
} // namespace systems
