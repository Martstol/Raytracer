#include "raytracer.hpp"
#include "sphere.hpp"

#include <glm/gtx/constants.hpp>

#include <memory>

int main(int argc, char * argv[]) {
	char const * out = "out.png";
	size_t width = 640;
	size_t height = 480;
	if (argc == 2) {
		out = argv[1];
	} else if (argc == 3) {
		out = argv[1];
		width = height = atoi(argv[2]);
	} else if (argc == 4) {
		out = argv[1];
		width = atoi(argv[2]);
		height = atoi(argv[3]);
	}

	rt::camera camera;
	camera.position = glm::vec3(-10.f, 0.f, 0.f);
	camera.direction = glm::vec3(1.f, 0.f, 0.f);
	camera.up = glm::vec3(0.f, 1.f, 0.f);
	camera.fov = glm::pi<float>()/3.f;

	rt::scene world;

	rt::light light;
	light.intensity = 1E14f;
	light.position = glm::vec3(0, 0.f, 1E8f);
	world.lights.push_back(light);

	auto s0 = std::unique_ptr<rt::sphere>(new rt::sphere());
	s0->center = glm::vec3(5, 0, 0);
	s0->radius = 1.5f;
	world.models.push_back(std::move(s0));

	auto s1 = std::unique_ptr<rt::sphere>(new rt::sphere());
	s1->center = glm::vec3(5, 0, -6);
	s1->radius = 3;
	world.models.push_back(std::move(s1));

	auto image = rt::raytrace(camera, world, width, height);
	rt::bitmap::save(image, out);
	return 0;
}
