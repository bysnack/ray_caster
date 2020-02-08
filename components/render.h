#pragma once

#include <tuple>
#include <SFML/Graphics.hpp>


namespace components {

	using render = std::tuple<
		sf::PrimitiveType,
		std::vector<sf::Vertex>,
		sf::RenderStates
	>;
}