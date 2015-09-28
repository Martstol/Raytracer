#include "light.hpp"

namespace rt {

	float getLightAttenuation(float distance) {
		float kc = 1.f;
		float kl = .1f;
		float kq = .01f;
		return 1.f / (kc + kl*distance + kq*distance*distance);
	}

}

