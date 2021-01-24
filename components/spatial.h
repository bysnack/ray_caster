#pragma once

#include "../utils/coordinates/coordinates.h"


namespace components {

	struct spatial {
		utils::coordinates::world position{ 30.f, 30.f };
		utils::coordinates::world dimensions{ 1.f, 1.f };
	};
};
