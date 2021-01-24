#include "collision.h"
#include "../components/components.h"
#include "../utils/vector.h"

/*
 *   Anonymous namespace
 *
 *   @brief  Contains a set of helper functions used to detect collisions
 */
namespace {
/*
 *   Heading to pos modifier
 *
 *   @brief              Calculates a position modifier depending on the current
 * heading
 *   @param  heading     The heading entity of the movable component
 *   @returns            The calculated position modifier
 */
utils::coordinates::world heading_to_pos_modifier(components::heading heading) {
  utils::coordinates::world modifier{0.f, 0.f};
  switch (heading) {
  case components::heading::east:
    modifier = {-1.f, 0.f};
    break;
  case components::heading::west:
    modifier = {1.f, 0.f};
    break;
  case components::heading::south:
    modifier = {0.f, -1.f};
    break;
  case components::heading::north:
    modifier = {0.f, 1.f};
    break;
  }
  return modifier;
}

/*
 *   Cells colision detecter
 *
 *   @brief              Detects collisions between a movable and a group of
 * cells
 *   @param  cells       The group of cells
 *   @param  component   The component to detect collisions with
 *   @returns            Whether a collision was detected or not
 */
template <class entity_t>
bool detect_collision(const std::vector<entities::cell> &cells,
                      const entity_t &entity) {
  auto &[e_position, e_dimensions] = std::get<components::spatial>(entity);
  auto [ecx, ecy] = e_position - (e_dimensions / 2);

  for (auto &&cell : cells) {
    auto &[c_position, c_dimensions] = std::get<components::spatial>(cell);
    const auto &[cx, cy] = c_position;
    if (ecx < cx + c_dimensions.x && ecx + e_dimensions.x > cx &&
        ecy < cy + c_dimensions.y && ecy + e_dimensions.y > cy) {
      return true;
    }
  }
  return false;
}
} // namespace

namespace systems {
void collision(entities::entities &container) noexcept {
  // only movables can collisionate
  container.apply_for<components::spatial, components::speed,
                      components::heading>([&](auto &&entity) {
    // detect collisions with map cells
    if (detect_collision(container.get<entities::cell>(), entity)) {
      // step back if a collision was detected
      std::get<components::spatial>(entity).position +=
          heading_to_pos_modifier(std::get<components::heading>(entity)) *
          std::get<components::speed>(entity);
    }
  });
}
} // namespace systems
