#pragma once

#include <glm/glm.hpp>

namespace rt {
	struct Camera {
		glm::vec3 position;
		glm::vec3 direction;
		glm::vec3 up;
		float fov;
	};
}
