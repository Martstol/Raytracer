#pragma once

#include "ray.hpp"
#include "intersection.hpp"
#include "color.hpp"

namespace rt {

	struct Model {

		virtual intersection intersects(ray ray) const = 0;
		virtual ~Model();
		virtual color getColor() const = 0;
		
	};

}
