#pragma once

#include "globals.hpp"
#include "mat4.hpp"
#include "utils.hpp"
#include "vec2.hpp"

namespace simulation {
	class AutonomousAgent {
	public:
		maths::vec3 translation;
		maths::vec3 rotation;
		maths::vec3 scale;

		maths::vec2f velocity;
		maths::vec2f acceleration;
		float mass;

		maths::mat4 model_matrix;

		AutonomousAgent() :
			translation(
				utils::gen_random(0.f, static_cast<float>(utils::resolution()[0])), 
				utils::gen_random(0.f, static_cast<float>(utils::resolution()[1])), 
				0.f
			),
			rotation(0.f),
			velocity(0.f),
			acceleration(0.f),
			scale(maths::vec3(utils::gen_random(2.f, 32.f))),
			mass(maths::magnitude(scale)) {
		}

		void update();
		void apply_force(const maths::vec2f& force);

	private:
		friend class Simulation;
	};
}
