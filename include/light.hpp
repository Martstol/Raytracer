#pragma once

#include "color.hpp"

#include <glm/glm.hpp>

namespace rt {
	
	struct Light {
		glm::vec3 position;
		Color color;
		float intensity;
	};

	float getLightAttenuation(float distance);

}
