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
        emplace(std::forward<Entities>(entities)...);
      }

      /**
       *  @brief            Emplaces a component into the container
       *  @param  entity    The entity to emplace
       *  @param  entities  The rest of entities to emplace next
       */
      template<class Entity, class ...Entities>
      constexpr void emplace(Entity&& entity, Entities&& ...entities) {
        emplaceImpl(std::make_shared<Entity>(std::forward<Entity>(entity)));
        if constexpr (sizeof... (Entities) > 0) {
          emplace(std::forward<Entities>(entities)...);
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
      /**
       *  @brief            Recursive component emplacement implementation function
       *  @param  entity    A shared pointer to the entity used to create the component
       */
      template<class Entity, size_t Index = 0>
      constexpr void emplaceImpl(std::shared_ptr<Entity> entity) {
        using Comp = std::tuple_element_t<Index, underlying_type>;
        if constexpr (belongsToComponent<Entity, Comp>::value) {
          std::get<Index>(_components).entities.push_back(entity);
        }

        if constexpr (Index < std::tuple_size_v<underlying_type> - 1) {
          emplaceImpl<Entity, Index + 1>(std::move(entity));
        }
      }

    private:
      underlying_type _components;
  };
}