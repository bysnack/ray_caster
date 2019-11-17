#pragma once

#include "Entities/Entities.h"
#include "Components/Components.h"

class ComponentContainer {
  public:
    template<class ...Entities>
    ComponentContainer(Entities&& ...entities)
    {
      push(std::forward<Entities>(entities)...);
    }

    template<class Entity, class ...Rest>
    void push(Entity entity, Rest ...entities) {
      if constexpr (Entities::is_renderizable_v<Entity>) {
        std::get<Components::Drawable>(components[0]).entities.push_back(
          std::make_shared<Components::Drawable::Held>(entity)
        );
      }
      if constexpr (Entities::is_initializable_v<Entity>) {
        std::get<Components::Initializable>(components[1]).entities.push_back(
          std::make_shared<Components::Initializable::Held>(entity)
        );
      }

      if constexpr (sizeof... (entities) > 0) push(std::forward<Rest>(entities)...);
    }

    template<class Component, class Function>
    void apply(Function&& function) {
      for (auto&& entity : std::get<Component>(components[Component::id]).entities) {
        std::visit([&function](auto&& elem){
          function(elem);
        }, *entity);
      }
    }

  private:
    std::array<Components::Component, 2> components{ Components::Drawable{}, Components::Initializable{} };
};