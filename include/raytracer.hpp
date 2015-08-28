#pragma once

#include "bitmap.hpp"
#include "camera.hpp"
#include "scene.hpp"

namespace rt {
	
	bitmap raytrace(camera const camera, scene const& world, size_t const width, size_t const height);

}
