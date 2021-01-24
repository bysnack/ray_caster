#pragma once

#include "../components/components.h"

namespace entities {
	using player = std::tuple<
		components::render,
		components::spatial,
		components::speed,
		components::heading,
		components::light
	>;
}
