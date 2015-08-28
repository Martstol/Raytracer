#pragma once

#include "sphere.hpp"

#include <glm/glm.hpp>

#include <limits>

namespace rt {
	
	struct intersection {
		sphere const * model = nullptr;
		glm::vec3 normal;
		glm::vec3 point;
		float distance = std::numeric_limits<float>::infinity();
	};

}

