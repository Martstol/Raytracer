#pragma once

#include "sphere.hpp"
#include "light.hpp"

#include <vector>

namespace rt {

	struct scene {
		std::vector<sphere> models;
		std::vector<light> lights;

	};

}
