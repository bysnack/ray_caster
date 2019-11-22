#pragma once

#include <type_traits>

namespace Utils {

  template<class T, class U>
  struct TypeList {
    using Head = T;
    using Tail = U;
  };

  struct NullType{};
}
