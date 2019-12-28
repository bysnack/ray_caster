#pragma once

#include "../entities/entities.h"


namespace systems {
	/*
	*   Collision system.
	*
	*   @brief  Handles collisions for movable entities 
	*/
	class collision {
	public:
		collision(entities::entities& container) noexcept;
		void operator()() noexcept;
	private:
		entities::entities& _entities;
	};
}
