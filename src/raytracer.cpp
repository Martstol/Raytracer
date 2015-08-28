#include "raytracer.hpp"

namespace rt {

	bitmap raytrace(size_t width, size_t height) {
		bitmap image(width, height);
		for (size_t i = 0; i < image.size(); i++) {
			image(i, 0) = pixel_t(255, 0, 0);
		}
		return image;
	}

}

