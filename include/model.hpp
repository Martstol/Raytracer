#pragma once

#include "ray.hpp"
#include "intersection.hpp"
#include "color.hpp"

namespace rt {

	struct model {

		virtual intersection intersects(ray ray) const = 0;
		virtual ~model();
		virtual color getColor() const = 0;
		
	};

}
