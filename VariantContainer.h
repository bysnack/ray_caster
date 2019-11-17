#pragma once

#include <variant>
#include <array>

template <class ...Elements>
class VariantContainer {
  public:
    using Element = std::variant<Elements...>;
    VariantContainer(Elements&& ...elements) : 
      _elements{ std::forward<Elements>(elements)...}
    {}

    auto begin()            noexcept  { return _elements.begin();   }
    auto end()              noexcept  { return _elements.end();     }
    decltype(auto) cbegin() noexcept  { return _elements.cbegin();  }
    decltype(auto) cend()   noexcept  { return _elements.cend();    }
    decltype(auto) size()   noexcept  { return _elements.size();    }
    decltype(auto) data()   noexcept  { return _elements.data();    }

  protected:
    std::array<Element, sizeof... (Elements)> _elements;
};