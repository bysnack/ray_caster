#pragma once

#include "Entities/Entities.h"

struct NullType {};

template<class T, class U>
struct TypeList {
  using head = T;
  using tail = U;
};

using DrawableComponents = TypeList<Line, TypeList<MapEntity, NullType>>;
using InitializableComponents = TypeList<MapEntity, NullType>;

template<class TList, class T> struct IndexOf;

template<class T>
struct IndexOf<NullType, T>
{
  static constexpr int8_t value = -1;
};

template<class T, class Tail>
struct IndexOf<TypeList<T, Tail>, T>
{
  static constexpr int8_t value = 0;
};

template<class Head, class Tail, class T>
struct IndexOf<TypeList<Head, Tail>, T>
{
  private:
    static constexpr int8_t temp = IndexOf<Tail, T>::value;
  public:
    static constexpr int8_t value = temp == -1 ? -1 : 1 + temp;
};

template<class Head, class Tail> struct TypeAt;

template<class Head, class Tail>
struct TypeAt<TypeList<Head, Tail>, 0>{
  using Result = Head;
};

template<class Head, class Tail, uint32_t i>
struct TypeAt<TypeList<Head, Tail>, i> {
  using Result = typename TypeAt<Tail, i - 1>::Result;
};


