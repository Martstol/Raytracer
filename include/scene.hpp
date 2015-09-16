#pragma once

#include "model.hpp"
#include "light.hpp"
#include "color.hpp"

#include <memory>
#include <vector>

namespace rt {

	struct scene {
		std::vector<std::unique_ptr<model>> models;
		std::vector<light> lights;
		color bgColor = color(0.05f, 0.1f, 0.25f);
	};

}
