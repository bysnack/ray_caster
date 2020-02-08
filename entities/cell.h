#pragma once

#include "../components/render.h"
#include "../components/position.h"
#include "../components/dimensions.h"


namespace entities {

	struct cell {
		components::render      render;
		components::position    position;
		components::dimensions  dimensions;
	};
}

