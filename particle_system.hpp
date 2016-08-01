#pragma once

#include <iterator>
#include "forces.hpp"
#include "globals.hpp"
#include "shader.hpp"
#include "mat4.hpp"
//#include "autonomous_agent.hpp"


namespace graphics {
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
			scale(maths::vec3(utils::gen_random(2.f, 32.f))),
			velocity(0.f),
			acceleration(0.f),
			mass(scale[0]) {
		}
	};

	class ParticleSystem {
	public:
		ParticleSystem(int num_particles = 10, const std::vector<maths::vec3>& vertices = {}) :
			vertices(vertices), 
			agents(), 
			transform_matrices(), 
			random_initiation(true)
		{
			for (int i = 0; i < num_particles; ++i) {
				AutonomousAgent a;
				agents.push_back(a);
				transform_matrices.push_back(a.model_matrix);
			}
		}

		void init_particle_system();
		void update_particle_system();
		void draw_particle_system();
		void destroy_particle_system();

		size_t size() { return agents.size(); }

	private:
		GLuint vao;
		GLuint position_vbo;
		GLuint matrix_vbo;

		utils::Shader shader;

		std::vector<maths::vec3> vertices;
		std::vector<AutonomousAgent> agents;
		std::vector<maths::mat4> transform_matrices;


		// Compute shader updating?
		void constrain_particle(AutonomousAgent& a);
		void update_particle(AutonomousAgent& a);
		void apply_force(AutonomousAgent& a, const maths::vec2f& force);

		bool random_initiation;
	};
}