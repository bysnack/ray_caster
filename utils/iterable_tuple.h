#include <tuple>

template<template<class element_t> class trait_t, class tuple_t, class = void>
struct subtuple {
	using type = std::tuple<>;
};

template<template<class element_t> class trait_t, class tuple_head_t, class ...tuple_elements_t>
struct subtuple<trait_t, std::tuple<tuple_head_t, tuple_elements_t...>, std::enable_if_t<!trait_t<tuple_head_t>::value>> {
	using type = typename subtuple<trait_t, std::tuple<tuple_elements_t...>>::type;
};

template<template<class element_t> class trait_t, class tuple_head_t, class ...tuple_elements_t>
struct subtuple<trait_t, std::tuple<tuple_head_t, tuple_elements_t...>, std::enable_if_t<trait_t<tuple_head_t>::value>> {
	using type = decltype(std::tuple_cat(
		std::declval<std::tuple<std::add_lvalue_reference_t<tuple_head_t>>>(),
		std::declval<subtuple<trait_t, tuple_elements_t...>::type>()
	));
};

template<template<class> class trait_t, class tuple_element_t>
decltype(auto) forward_if_satisfies_trait(tuple_element_t&& tuple_elem) {
	if constexpr (trait_t<std::remove_reference_t<tuple_element_t>>::value) {
		return std::forward_as_tuple(tuple_elem);
	}
	else {
		return std::forward_as_tuple();
	}
}

template<template<class element_t> class trait_t, class tuple_t>
decltype(auto) subtie(tuple_t&& tuple) {
	return std::apply([&](auto&& ...elem) { return std::tuple_cat(forward_if_satisfies_trait<trait_t>(elem)...); }, tuple);
}

template<class ...elements_t>
class iterable_tuple {
public:
	using underlying_tuple = std::tuple<elements_t...>;
	template<class handler_t, size_t index_v = 0>
	void for_each(handler_t&& handler) {
		std::apply([handler = std::forward<handler_t>(handler)](auto&& elem) { (handler(elem), ...); });
	}

private:
	underlying_tuple _elements;
};
