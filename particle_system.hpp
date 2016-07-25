#pragma once

#include <iterator>
#include <thread>

#include "forces.hpp"
#include "globals.hpp"
#include "shader.hpp"
#include "autonomous_agent.hpp"

namespace graphics {
	class ParticleSystem {
	public:
		ParticleSystem() : agents(nullptr), agent_transform_matrices(nullptr), random_initiation(true), num_particles(256) { }

		void init_particle_system(const std::vector<maths::vec3>& vertices);
		void update_particle_system();
		void draw_particle_system();
		void destroy_particle_system();

		int num_particles;

	private:
		
		bool random_initiation;

		GLuint vao;
		GLuint position_vbo;
		GLuint matrix_vbo;

		utils::Shader shader;

		
		simulation::AutonomousAgent* agents;
		maths::mat4* agent_transform_matrices;

		
	};
}