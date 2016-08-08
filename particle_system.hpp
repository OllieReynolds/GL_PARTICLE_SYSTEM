#pragma once

#include <iterator>
#include "forces.hpp"
#include "globals.hpp"
#include "shader.hpp"
#include "mat4.hpp"

namespace graphics {
	struct Particle {
		maths::vec2f position;
		maths::vec2f velocity;
		float scale;
		float mass;

		Particle() :
			position(
				utils::gen_random(0.f, static_cast<float>(utils::resolution()[0])), 
				utils::gen_random(0.f, static_cast<float>(utils::resolution()[1]))
			),
			scale(utils::gen_random(2.f, 32.f)),
			mass(scale),
			velocity(0.f)
		{ }
	};

	class ParticleSystem {
	public:
		ParticleSystem(int num_particles = 10, const std::vector<maths::vec3>& vertices = {}) :
			particle_vertex_data(vertices),
			particle_objects(),
			particle_matrices()
		{
			for (int i = 0; i < num_particles; ++i) {
				particle_objects.push_back(Particle());
				particle_matrices.push_back(maths::mat4());
			}
		}

		void init_particle_system();
		void update_particle_system();
		void draw_particle_system();
		void destroy_particle_system();

		std::string print_compute_shader_info();

		size_t size() { return particle_objects.size(); }

	private:
		GLuint vao;
		GLuint vertex_vbo;
		//GLuint matrix_vbo;

		GLuint particle_ssbo;
		GLuint matrix_ssbo;

		utils::Shader compute_shader;
		utils::Shader render_shader;
		
		std::vector<Particle>    particle_objects;
		std::vector<maths::mat4> particle_matrices;
		std::vector<maths::vec3> particle_vertex_data;
	};
}