#pragma once

#include "model.hpp"
#include "light.hpp"
#include "color.hpp"

#include <memory>
#include <vector>

namespace rt {

	struct Scene {
		std::vector<std::unique_ptr<model>> models;
		std::vector<light> lights;
		Color bgColor = color(0.05f, 0.1f, 0.25f);
	};

}
