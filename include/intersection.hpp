#pragma once

#include <glm/glm.hpp>

#include <limits>

namespace rt {

	struct model;
	
	struct intersection {
		model const * model = nullptr;
		glm::vec3 normal;
		glm::vec3 point;
		float distance = std::numeric_limits<float>::infinity();
	};

}

