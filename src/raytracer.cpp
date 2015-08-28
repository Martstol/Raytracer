#include "raytracer.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "light.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

#include <iostream>

namespace rt {

	float getColor(glm::vec3 const point, glm::vec3 const normal, light const light) {
		glm::vec3 const dir = glm::normalize(light.position - point);
		return 255*std::max(0.f, glm::dot(dir, normal));
	}

	pixel_t shootRay(ray const ray, sphere const sphere, light const light) {
		glm::vec3 point, normal;
		if (glm::intersectRaySphere(ray.origin, ray.direction, sphere.center, sphere.radius, point, normal)) {
			return pixel_t(getColor(point, normal, light));
		}
		return pixel_t(15, 30, 90);
	}

	bitmap raytrace(camera const camera, size_t const width, size_t const height) {
		bitmap image(width, height);
		
		auto const right = glm::cross(camera.direction, camera.up);
		auto const center = camera.position + camera.direction;
		float const pixelSize = tan(camera.fov/2.f) / (height/2.f);

		sphere sphere;
		sphere.center = glm::vec3(5, 0, 0);
		sphere.radius = 1;

		light light;
		light.position = glm::vec3(-1E9f, 0, 1E9f);

		for (size_t row = 0; row < height; row++) {
			for (size_t col = 0; col < width; col++) {
				float const x = col - width / 2.f;
				float const y = row - height / 2.f;

				ray ray;
				ray.origin = camera.position;
				ray.direction = glm::normalize((center + right*x*pixelSize + camera.up*y*pixelSize) - ray.origin);

				image(col, row) = shootRay(ray, sphere, light);
			}
		}

		return image;
	}

}

