#include "sphere.hpp"

rt::intersection rt::sphere::intersects(rt::ray ray) const {
	rt::intersection isect;
	glm::vec3 point, normal;

	if (glm::intersectRaySphere(ray.origin, ray.direction, center, radius, point, normal)) {
		isect.distance = glm::distance(ray.origin, point);
		isect.point = point;
		isect.normal = normal;
		isect.model = this;
	}

	return isect;
}

