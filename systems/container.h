#pragma once

#include <variant>
#include <array>

namespace systems {
  template <class ...systems_t>
  class container {
    public:
      using variant_container = std::array<std::variant<systems_t...>, sizeof... (systems_t)>;

      container(systems_t&& ...systems) :
        _systems{ std::forward<systems_t>(systems)... }
      {}

      template<class components_t>
      void run_all(components_t&& components) {
        // iterate through all the systems
        for (auto&& elem : _systems) {
          // visit the variant
          std::visit([&components](auto&& system){
            // run the system with the components
            system(std::forward<components_t>(components));
          }, elem);
        }
      }
    private:
      variant_container _systems;
  };
}
