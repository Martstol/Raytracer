#include "raytracer.hpp"
#include "ray.hpp"
#include "intersection.hpp"
#include "color.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

#include <iostream>
#include <cmath>

namespace rt {

	intersection findClosestIntersection(ray const ray, scene const& world) {
		intersection isect;
		for (size_t i = 0; i < world.models.size(); i++) {
			model * model = world.models[i].get();
			intersection potential = model->intersects(ray);
			if (potential.model != nullptr && potential.distance < isect.distance) {
				isect = potential;
			}
		}
		return isect;
	}

	float getLightAttenuation(float distance) {
		float kc = 1.f;
		float kl = .1f;
		float kq = .01f;
		return 1.f / (kc + kl*distance + kq*distance*distance);
	}

	color getLightContribution(intersection const intersection, light const light, scene const& world) {
		ray ray;
		ray.origin = intersection.point + 0.0001f * intersection.normal;
		ray.direction = glm::normalize(light.position - ray.origin);

		auto occlusion = findClosestIntersection(ray, world);
		if (occlusion.model != nullptr) {
			return color(0);
		}

		float distance = glm::distance(light.position, ray.origin);
		float i = glm::dot(ray.direction, intersection.normal) * light.intensity * getLightAttenuation(distance);

		return color(glm::clamp(i, 0.f, 1.f));
	}

	color calculateLocalColorModel(intersection const intersection, scene const& world) {
		color color(0);

		for (light const light : world.lights) {
			color += getLightContribution(intersection, light, world);
		}

		return color;
	}

	color shootRay(ray const ray, scene const& world) {
		intersection const intersection = findClosestIntersection(ray, world);
		if (intersection.model == nullptr) {
			return world.bgColor;
		}

		return calculateLocalColorModel(intersection, world);	
	}

	bitmap raytrace(camera const camera, scene const& world, size_t const width, size_t const height) {
		bitmap image(width, height);
		
		auto const right = glm::cross(camera.direction, camera.up);
		auto const center = camera.position + camera.direction;
		float const pixelSize = std::tan(camera.fov/2.f) / (height/2.f);

		for (size_t row = 0; row < height; row++) {
			for (size_t col = 0; col < width; col++) {
				float const x = col - width / 2.f;
				float const y = row - height / 2.f;

				ray ray;
				ray.origin = camera.position;
				ray.direction = glm::normalize((center + right*x*pixelSize + camera.up*y*pixelSize) - ray.origin);

				image(col, height - (row + 1)) = pixel_t(shootRay(ray, world));
			}
		}

		return image;
	}

}

