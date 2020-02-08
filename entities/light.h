#pragma once

#include "../components/components.h"
#include <SFML/Graphics/Texture.hpp>

namespace entities {

	struct light {
		components::render render;
		components::position position	{ 40.f, 30.f	};
		components::dimensions dimensions{ 80.f, 60.f	};
		sf::Texture texture;
	};
}