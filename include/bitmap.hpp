#pragma once

#include "color.hpp"

#include <png++/png.hpp>

#include <vector>
#include <cstdint>
#include <string>

namespace rt {

	struct pixel_t {
		uint8_t r, g, b, a;

		explicit pixel_t() {}
		explicit pixel_t(uint8_t i) : r(i), g(i), b(i), a(255) {}
		pixel_t(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b), a(255) {}
		pixel_t(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}
		explicit pixel_t(color c) : r(255*c.r), g(255*c.g), b(255*c.b), a(255) {}
	};
	
	using size_t = std::size_t;

	struct bitmap {
		private:
			size_t width, height;
			std::vector<pixel_t> pixels;

			size_t index(size_t x, size_t y) const noexcept {return x + y*width;}

		public:
			bitmap(size_t width, size_t height) : width(width), height(height), pixels(width*height) {}

			size_t size() const noexcept {return width*height;}
			size_t getWidth() const noexcept {return width;}
			size_t getHeight() const noexcept {return height;}

			pixel_t const& operator()(size_t x, size_t y) const {return pixels[index(x, y)];}
			pixel_t & operator()(size_t x, size_t y) {return pixels[index(x, y)];}

			pixel_t const * data() const noexcept {return pixels.data();}
			pixel_t * data() noexcept {return pixels.data();}

			static void save(bitmap image, std::string file) {
				png::image<png::rgb_pixel> png(image.width, image.height);
				
				for (size_t y = 0; y < image.height; y++) {
					for (size_t x = 0; x < image.width; x++) {
						pixel_t c = image(x, y);
						png[y][x] = png::rgb_pixel(c.r, c.g, c.b);
					}
				}

				png.write(file);
			}
	};

}
