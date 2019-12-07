#pragma once

#include "../components/components.h"
#include <optional>
#include "../utils/vector.h"

namespace systems {
  class collision {
    public:
      void operator()(components::container& container) {
        // handle collisions
        decltype(auto) cells = container.get<components::cells>;
        container.apply_if<components::is_movable>([&](auto&& elem){
          for (auto&& cell : cells) {
            if (auto collision = detectCollision())
            elem.position += collision;
          }
        });
      }

    private:
      std::optional<utils::vector<float>> detectCollision(const components::container::components<components::cells>& cells, const entities::position& position) {
        for (auto&& cell : cells) {
          if (position.x < cell.second.position.x + cell.second.position.width 
            && position.x + position.width > cell.second.position.x 
            && position.y < cell.second.position.y + cell.second.position.height 
            && position.height + position.y > cell.second.position.y) {
          }

        }
  }
}