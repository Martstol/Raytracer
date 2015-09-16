#pragma once

#include "ray.hpp"
#include "intersection.hpp"

namespace rt {

	struct model {

		virtual intersection intersects(ray ray) const = 0;
		
	};

}
