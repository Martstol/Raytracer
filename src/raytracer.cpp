#include "raytracer.hpp"
#include "ray.hpp"
#include "intersection.hpp"
#include "color.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

#include <iostream>

namespace rt {

	intersection findClosestIntersection(ray const ray, scene const& world) {
		intersection intersection;
		for (size_t i = 0; i < world.models.size(); i++) {
			glm::vec3 point, normal;
			float distance = 0;
			sphere const& sphere = world.models[i];
			if (glm::intersectRaySphere(ray.origin, ray.direction, sphere.center, sphere.radius, point, normal)) {
				distance = glm::distance(ray.origin, point);
				if (distance < intersection.distance) {
					intersection.point = point;
					intersection.normal = normal;
					intersection.model = &world.models[i];
					intersection.distance = distance;
				}
			}
		}
		return intersection;
	}

	color getLightContribution(intersection const intersection, light const light, scene const& world) {
		ray ray;
		ray.origin = intersection.point + 0.0001f * intersection.normal;
		ray.direction = glm::normalize(light.position - ray.origin);

		auto occlusion = findClosestIntersection(ray, world);
		if (occlusion.model != nullptr) {
			return color(0);
		}

		float i = glm::dot(ray.direction, intersection.normal);

		return color(std::max(0.f, i));
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
		glm::vec3 const dir = glm::normalize(ray.origin - intersection.point);
		return color(std::max(0.f, glm::dot(dir, intersection.normal)));
		
	}

	bitmap raytrace(camera const camera, scene const& world, size_t const width, size_t const height) {
		bitmap image(width, height);
		
		auto const right = glm::cross(camera.direction, camera.up);
		auto const center = camera.position + camera.direction;
		float const pixelSize = tan(camera.fov/2.f) / (height/2.f);

		for (size_t row = 0; row < height; row++) {
			for (size_t col = 0; col < width; col++) {
				float const x = col - width / 2.f;
				float const y = row - height / 2.f;

				ray ray;
				ray.origin = camera.position;
				ray.direction = glm::normalize((center + right*x*pixelSize + camera.up*y*pixelSize) - ray.origin);

				image(col, row) = pixel_t(shootRay(ray, world));
			}
		}

		return image;
	}

}

