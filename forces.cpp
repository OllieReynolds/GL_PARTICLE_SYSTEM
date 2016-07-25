#include "forces.hpp"

namespace physics {
	maths::vec2f calc_friction(
		const float intensity, 
		const maths::vec2f& velocity
	) {
		return normalise(velocity * -1.f) * intensity;
	}

	maths::vec2f calc_wind(
		const float intensity
	) {
		float t = utils::elapsed_time<float>();
		return maths::vec2f(cosf(t), sinf(t)) * intensity;
	}

	maths::vec2f calc_gravity(
		const float intensity, 
		const float mass
	) {
		return maths::vec2f(0.f, -1.f * intensity) * mass;
	}

	maths::vec2f calc_drag(
		const float intensity, 
		const maths::vec2f& velocity
	) {
		return normalise(velocity * -1.f) * magnitude_squared(velocity) * intensity;
	}

	maths::vec2f calc_gravity(
		const float intensity, 
		const maths::vec2f& attractorPos, const float attractorMass,
		const maths::vec2f& particlePos, const float particleMass
	) {
		maths::vec2f direction = maths::normalise(attractorPos - particlePos);

		return maths::vec2f();
	}
}
