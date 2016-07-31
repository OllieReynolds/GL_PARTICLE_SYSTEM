#include "forces.hpp"

namespace physics {
	maths::vec2f calc_friction(const float intensity, const maths::vec2f& velocity) {
		return normalise(velocity * -1.f) * intensity;
	}

	maths::vec2f calc_wind(
		const float intensity) {
		return maths::vec2f(0.5, 1.0) * intensity;
	}

	maths::vec2f calc_gravity(const float intensity, const float mass) {
		return maths::vec2f(0.f, -1.f * intensity) * mass;
	}

	maths::vec2f calc_drag(const float intensity, const maths::vec2f& velocity) {
		return normalise(velocity * -1.f) * magnitude_squared(velocity) * intensity;
	}

	maths::vec2f calc_gravity(
		const float intensity, 
		const maths::vec2f& attractor_location, const float attractor_mass,
		const maths::vec2f& particle_location, const float particle_mass) 
	{
		maths::vec2f force = attractor_location - particle_location;
		float distance = magnitude_squared(force);
		float m = (intensity * attractor_mass * particle_mass) / distance * distance;
		return normalise(force) * m;
	}
}
