#pragma once

#include "VariantContainer.h"
#include <gsl/span>

template <class ...Systems>
class SystemContainer : public VariantContainer<Systems...>{
  public:
    SystemContainer(Systems&& ...systems) :
      VariantContainer<Systems...>{ std::forward<Systems>(systems)...  }
    {}

    template<class Components>
    void run_all(Components&& components) {
      // iterate through all the systems
      for (auto&& elem : VariantContainer<Systems...>::_elements) {
        // visit the variant
        std::visit([&components](auto&& system){
          // run the system with the components
          system.run(std::forward<Components>(components));
        }, elem);
      }
    }
};