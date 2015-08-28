#pragma once

#include "sphere.hpp"
#include "light.hpp"
#include "color.hpp"

#include <vector>

namespace rt {

	struct scene {
		color bgColor = color(0.05f, 0.1f, 0.25f);

		std::vector<sphere> models;
		std::vector<light> lights;

	};

}
