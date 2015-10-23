#pragma once

#include "bitmap.hpp"
#include "camera.hpp"
#include "scene.hpp"

namespace rt {
	
	Bitmap raytrace(Camera const camera, Scene const& world, size_t const width, size_t const height);

}
