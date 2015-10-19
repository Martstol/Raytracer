#include "raytracer.hpp"
#include "ray.hpp"
#include "intersection.hpp"
#include "color.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

#include <iostream>
#include <cmath>

rt::intersection findClosestIntersection(rt::ray const ray, rt::scene const& world) {
	rt::intersection isect;
	for (size_t i = 0; i < world.models.size(); i++) {
		rt::model * model = world.models[i].get();
		rt::intersection potential = model->intersects(ray);
		if (potential.model != nullptr && potential.distance < isect.distance) {
			isect = potential;
		}
	}
	return isect;
}

rt::color getLightContribution(rt::intersection const intersection, rt::light const light, rt::scene const& world) {
	rt::ray ray;
	ray.origin = intersection.point + 0.0001f * intersection.normal;
	ray.direction = glm::normalize(light.position - ray.origin);

	auto occlusion = findClosestIntersection(ray, world);
	if (occlusion.model != nullptr) {
		return rt::color(0);
	}

	float distance = glm::distance(light.position, ray.origin);
	float i = glm::dot(ray.direction, intersection.normal) * light.intensity * rt::getLightAttenuation(distance);

	return rt::color(i);
}

rt::color calculateLocalColorModel(rt::intersection const intersection, rt::scene const& world) {
	rt::color lightColor(0);

	for (rt::light const & light : world.lights) {
		lightColor += getLightContribution(intersection, light, world);
	}

	return intersection.model->getColor()*glm::clamp(lightColor, 0.f, 1.f);
}

rt::color shootRay(rt::ray const ray, rt::scene const& world) {
	rt::intersection const intersection = findClosestIntersection(ray, world);
	if (intersection.model == nullptr) {
		return world.bgColor;
	}

	return calculateLocalColorModel(intersection, world);	
}

rt::bitmap rt::raytrace(rt::camera const camera, rt::scene const& world, size_t const width, size_t const height) {
	rt::bitmap image(width, height);
	
	auto const right = glm::cross(camera.direction, camera.up);
	auto const center = camera.position + camera.direction;
	float const pixelSize = std::tan(camera.fov/2.f) / (height/2.f);

	for (size_t row = 0; row < height; row++) {
		for (size_t col = 0; col < width; col++) {
		float const x = col - width / 2.f;
			float const y = row - height / 2.f;

			rt::ray ray;
			ray.origin = camera.position;
			ray.direction = glm::normalize((center + right*x*pixelSize + camera.up*y*pixelSize) - ray.origin);

			image(col, height - (row + 1)) = rt::pixel_t(shootRay(ray, world));
		}
	}

	return image;
}

