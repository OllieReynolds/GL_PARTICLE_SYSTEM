#pragma once

#include "vec2.hpp"
#include "utils.hpp"

namespace physics {
	maths::vec2f calc_wind(const float intensity);

	maths::vec2f calc_drag(const float intensity, const maths::vec2f& velocity);
	maths::vec2f calc_friction(const float intensity, const maths::vec2f& velocity);
	
	maths::vec2f calc_gravity(const float intensity, const float mass);
	maths::vec2f calc_gravity(
		const float intensity, 
		const maths::vec2f& attractor_position, const float attractor_mass,
		const maths::vec2f& particle_position, const float particle_mass);
}