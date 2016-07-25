#pragma once

#include "vec2.hpp"
#include "utils.hpp"

namespace physics {
	maths::vec2f calc_friction(const float intensity, const maths::vec2f& velocity);
	maths::vec2f calc_wind(const float intensity);
	maths::vec2f calc_gravity(const float intensity, const float mass);
	maths::vec2f calc_drag(const float intensity, const maths::vec2f& velocity);
	
	maths::vec2f calc_gravity(const float intensity, const maths::vec2f& attractorPos, const float attractorMass,
		const maths::vec2f& particlePos, const float particleMass);
}