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
		ParticleSystem(const std::vector<maths::vec3>& vertices = {}) :
			vertices(vertices), agents(), transform_matrices(), random_initiation(true
		) { 
			for (int i = 0; i < 256; ++i) {
				simulation::AutonomousAgent a;
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
		std::vector<maths::vec3> vertices;

		GLuint vao;
		GLuint position_vbo;
		GLuint matrix_vbo;

		utils::Shader shader;

		std::vector<simulation::AutonomousAgent> agents;
		std::vector<maths::mat4> transform_matrices;

		bool random_initiation;
	};
}