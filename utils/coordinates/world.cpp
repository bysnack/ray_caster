#include "world.h"
#include "screen.h"
#include "../../config.h"

namespace utils::coordinates {

	world::operator screen() const noexcept {
		return {
			roundf((x * config::RESOLUTION.first) / config::MAP_SIZE.first),
			roundf((y * config::RESOLUTION.second) / config::MAP_SIZE.second)
		};
	}

	world::operator tile() const noexcept {
		return {
			static_cast<int>(floorf(x)),
			static_cast<int>(floorf(y))
		};
	}
}
