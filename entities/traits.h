#pragma once

#include <type_traits>
#include <tuple>
#include "../components/components.h"

namespace entities {

	template<class entity_t, class = void>
	struct renderizable : public std::false_type{};

	template<class entity_t>
	struct renderizable<entity_t, std::enable_if_t<
		// render component present
		std::is_same_v<decltype(std::remove_cv_t<std::remove_reference_t<entity_t>>::render), components::render>
	>> : public std::true_type{};

	template<class entity_t, class = void>
	struct movable : public std::false_type{};

	template<class entity_t>
	struct movable<entity_t, std::void_t<
		// speed component present
		std::is_same<decltype(std::remove_cv_t<std::remove_reference_t<entity_t>>::speed), components::speed>,
		// position component present
		std::is_same<decltype(std::remove_cv_t<std::remove_reference_t<entity_t>>::position), components::position>,
		// heading component present
		std::is_same<decltype(std::remove_cv_t<std::remove_reference_t<entity_t>>::heading), components::heading>
	>> : public std::true_type{};

	template<class entity_t, class = void>
	struct collisionable : public std::false_type{};

	template<class entity_t>
	struct collisionable<entity_t, std::enable_if_t<
		// position component present
		std::is_same_v<decltype(std::remove_cv_t<std::remove_reference_t<entity_t>>::position), components::position>
	>> : public std::true_type{};

	template<class entity_t>
	struct true_trait : std::true_type{};

	template<class entity_t>
	constexpr bool renderizable_v = renderizable<entity_t>::value;

	template<class target_t, class entity_t>
	constexpr bool is_entity_v = std::is_same_v<std::remove_cv_t<std::remove_reference_t<target_t>>, entity_t>;
}
