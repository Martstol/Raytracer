#pragma once

#include "model.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

namespace rt {

	struct Sphere : Model {
		glm::vec3 center;
		float radius;
		color c;

		virtual Intersection intersects(ray ray) const override;
		virtual Color getColor() const override;
	};

}

