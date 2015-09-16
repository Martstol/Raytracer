#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

namespace rt {

	struct sphere : model {
		glm::vec3 center;
		float radius;

		virtual intersection intersects(ray ray) const override {
			intersection isect;
			glm::vec3 point, normal;

			if (glm::intersectRaySphere(ray.origin, ray.direction, center, radius, point, normal)) {
				isect.distance = glm::distance(ray.origin, point);
				isect.point = point;
				isect.normal = normal;
				isect.model = this;
			}

			return isect;
		}
	};

}

