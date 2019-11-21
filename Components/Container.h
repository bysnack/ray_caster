#pragma once

#include "Definitions.h"
#include "Traits.h"

namespace Components {

  class Container {
    public:
      using underlying_type = std::tuple<Drawable, Map, User>;

      /**
      *  @brief            Constructor
      *  @param  entities  The entities to be saved as coponents
      */
      template<class ...Entities>
      Container(Entities&& ...entities) noexcept
      {
        // derive work to push function
        add(std::forward<Entities>(entities)...);
      }

      template<class Entity, class ...Entities>
      constexpr void add(Entity&& entity, Entities&& ...entities) {
        addImpl(std::make_shared<Entity>(std::forward<Entity>(entity)));
        if constexpr (sizeof... (Entities) > 0) {
          add(std::forward<Entities>(entities)...);
        }
      }

      /**
      *  @brief            Applies a given function to an specified component
      *  @param  function  The function to apply
      *  @tparam Component The target component
      */
      template<class Component, class Function>
      void apply(Function&& function) {
        // get component and iterate through entities
        for (auto&& entity : std::get<Component>(_components).entities) {
          // visit the component
          std::visit([&function](auto&& elem){
            // invoke fuction with element
            function(*elem);
          }, entity);
        }
      }
    private:

      template<class Entity, size_t Index = 0>
      constexpr void addImpl(std::shared_ptr<Entity> entity) {
        using Comp = std::tuple_element_t<Index, underlying_type>;
        if constexpr (belongsToComponent<Entity, Comp>::value) {
          std::get<Index>(_components).entities.push_back(entity);
        }

        if constexpr (Index < std::tuple_size_v<underlying_type> - 1) {
          addImpl<Entity, Index + 1>(std::move(entity));
        }
      }

      underlying_type _components;
  };
}