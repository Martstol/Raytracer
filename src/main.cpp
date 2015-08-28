#include "raytracer.hpp"

#include <glm/gtx/constants.hpp>

int main(int argc, char * argv[]) {
	char const * out = "out.png";
	size_t width = 640;
	size_t height = 480;
	if (argc ==2) {
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
	camera.position = glm::vec3(0, 0.f, 0.f);
	camera.direction = glm::vec3(1.f, 0.f, 0.f);
	camera.up = glm::vec3(0.f, 1.f, 0.f);
	camera.fov = glm::pi<float>()/3.f;

	scene world;

	light light;
	light.position = glm::vec3(-1E9f, 0.f, 1E9f);
	world.lights.push_back(light);

	sphere s0;
	s0.center = glm::vec3(5, 0, 0);
	s0.radius = 5;
	world.models.push_back(s0);

	sphere s1;
	s1.center = glm::vec3(14.f, 0, -6.f);
	s1.radius = 7.5f;
	world.models.push_back(s1);

	auto image = rt::raytrace(camera, width, height);
	rt::bitmap::save(image, out);
	return 0;
}
