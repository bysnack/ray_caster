#pragma once

namespace Systems {

  class InitUser {
    public:
      template<class Component>
      InitMap(Component&& components)
      {
        components.template apply<Components::User>([](auto&& elem){
          auto tiles = initializeMap(elem.seed, elem.size);
          for (auto&& tile : tiles) {
            elem.render.push_back({sf::Quads, tile});
          }
        });
      }
  };
}