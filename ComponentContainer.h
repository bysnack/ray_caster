#pragma once

#include "Entities/Entities.h"
#include "Components/Components.h"
#include "Utils/TypeList.h"

namespace {
  /**
   *  @brief  Recursive pusher class, takes a TypeList of type traits
   *  @note   This is probably an over-engineered solution for the problem
   *          but what the heck, it was fun to make
   */
  template<class TL>
  struct RecursivePusher;

  /**
   *  @brief  Recursive pusher class, case base takes a TypeList of one type trait
   */
  template<class Head>
  struct RecursivePusher<Util::TypeList<Head, Util::NullType>> {
    /**
     *  @brief            Constructor
     *  @param  entity    The entity to push
     *  @param  container The cointaner where to push
     */
    template<class Entity, class Container>
    RecursivePusher<Util::TypeList<Head, Util::NullType>>(std::shared_ptr<Entity> entity, Container& container) {
      // if the type trait is valid
      if constexpr(Head::value) {
        // get the component and push a shared pointer to the entities list
        std::get<typename Head::Component>(container).entities.push_back(
          entity
        );        
      } 
    }
  };

  /**
   *  @brief  Recursive pusher class, takes a TypeList of type traits
   */
  template<class Head, class Tail>
  struct RecursivePusher<Util::TypeList<Head, Tail>> : public RecursivePusher<Tail> {
    /**
     *  @brief            Constructor
     *  @param  entity    The entity to push
     *  @param  container The cointaner where to push
     */
    template<class Entity, class Container>
    RecursivePusher<Util::TypeList<Head, Tail>>(std::shared_ptr<Entity> entity, Container& container) : 
      RecursivePusher<Tail>{entity, container}
    {
      // if the type trait is valid
      if constexpr(Head::value) {
        // get the component and push a shared pointer to the entities list
        std::get<typename Head::Component>(container).entities.push_back(
          entity
        );
      } 
    }
  };

  /**
   *  @brief  Recursive type alias with specific type traits
   */
  template<class Entity>
  using RecursivePusherWithTraits = RecursivePusher<
    Util::TypeList<
      Entities::is_renderizable<Entity>, 
      Util::TypeList<
        Entities::is_initializable<Entity>, 
        Util::NullType
      >
    >
  >;
}


/**
 *  @brief  Component container class
 */
class ComponentContainer {
  public:

    /**
     *  @brief            Constructor
     *  @param  entities  The entities to be saved as coponents
     */
    template<class ...Entities>
    ComponentContainer(Entities&& ...entities)
    {
      // derive work to push function
      push(std::forward<Entities>(entities)...);
    }

    /**
     *  @brief            Recursive push function
     *  @param  entity    The first entity to push
     *  @param  entities  The rest of the entities to push
     */
    template<class Entity, class ...Rest>
    void push(Entity entity, Rest ...entities) {
      // delegate pushing to the recursive pusher 
      RecursivePusherWithTraits<Entity>{ std::make_shared<Entity>(std::move(entity)), _components };

      // make the recursive call if there are more entities to push
      if constexpr (sizeof... (entities) > 0) push(std::forward<Rest>(entities)...);
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
    Components::Components _components;
};