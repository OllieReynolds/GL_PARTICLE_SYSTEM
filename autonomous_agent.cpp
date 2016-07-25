#include "autonomous_agent.hpp"

namespace simulation {
	void AutonomousAgent::apply_force(const maths::vec2f& force) {
		acceleration += force / mass;
	}

	void AutonomousAgent::update() {
		velocity += acceleration;
		translation += maths::vec3(velocity[0], velocity[1], 0.f);

		maths::vec3 offset = scale * 0.5f;
	
		if (translation[0] > utils::resolution()[0] - offset[0]) { 
			translation[0] = utils::resolution()[0] - offset[0];
			velocity[0] *= -1.f; 
		} 
		else if (translation[0] < offset[0]) {
			translation[0] = offset[0];
			velocity[0] *= -1.f; 
		}
	
		if (translation[1] > utils::resolution()[1] - offset[1]) {
			translation[1] = utils::resolution()[1] - offset[1];
			velocity[1] *= -1.f; 
		} 
		else if (translation[1] < offset[1]) {
			translation[1] = offset[1];
			velocity[1] *= -1.f; 
		}

		acceleration = {0.f};

		model_matrix.scale(scale).translate(translation);
	}
}