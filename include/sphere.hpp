#pragma once

#include "model.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

namespace rt {

	struct sphere : model {
		glm::vec3 center;
		float radius;

		virtual intersection intersects(ray ray) const override;
	};

}

