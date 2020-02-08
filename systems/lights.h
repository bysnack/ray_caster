#pragma once

#include "../entities/entities.h"

namespace systems {

	class lights {
	public:
		lights(entities::entities& container) noexcept;
		void operator()() noexcept;
	private:
		entities::entities& _entities;
	};
}
