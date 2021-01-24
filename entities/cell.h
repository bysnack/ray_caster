#pragma once

#include "../components/render.h"
#include "../components/position.h"
#include "../components/dimensions.h"


namespace entities {

	using cell = std::tuple<
		components::render,
		components::spatial
	>;
}

