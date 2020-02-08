#include "screen.h"
#include "world.h"
#include "../../config.h"

namespace utils::coordinates {

	screen::operator world() const noexcept {
		return {
			(x * config::MAP_SIZE.first) / config::RESOLUTION.first,
			(y * config::MAP_SIZE.second) / config::RESOLUTION.second
		};
	}

	screen::operator tile() const noexcept {
		return {
			static_cast<int>(std::floorf((x * config::MAP_SIZE.first) / config::RESOLUTION.first)),
			static_cast<int>(std::floorf((y * config::MAP_SIZE.second) / config::RESOLUTION.first))
		};
	}
}
