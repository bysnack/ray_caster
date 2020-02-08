#pragma once

#include "../components/components.h"

namespace entities {

	struct player {
		components::render      render;
		components::position    position  { 30.f, 30.f	                };
		components::speed       speed     { 0.25f                       };
		components::heading     heading   { components::heading::north  };
		components::dimensions  dimensions{ 1.f, 1.f	                };
	};
}