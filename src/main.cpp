#include "raytracer.hpp"

#include <iostream>

int main(int argc, char * argv[]) {
	auto image = rt::raytrace(640, 480);
	rt::bitmap::save(image, "out.png");
	return 0;
}
