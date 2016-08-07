#pragma once

#include <iterator>
#include "forces.hpp"
#include "globals.hpp"
#include "shader.hpp"
#include "mat4.hpp"

namespace graphics {
	struct Particle {
		maths::vec3 position;
		float padding0;

		maths::vec3 rotation;
		float padding1;

		maths::vec3 scale;
		float padding2;

		maths::vec2f velocity;
		maths::vec2f acceleration;

		float mass;
		maths::vec3 padding3;

		Particle() :
			position(utils::gen_random(0.f, static_cast<float>(utils::resolution()[0])), utils::gen_random(0.f, static_cast<float>(utils::resolution()[1])), 0.f),
			rotation(0.f),
			scale(maths::vec3(utils::gen_random(2.f, 32.f))),
			velocity(0.f),
			acceleration(0.f),
			mass(scale[0]) 
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

		size_t size() { return particle_objects.size(); }

	private:
		GLuint vao;
		GLuint position_vbo;
		GLuint matrix_vbo;

		GLuint particle_ssbo;

		utils::Shader compute_shader;
		utils::Shader render_shader;
		
		std::vector<Particle>    particle_objects;
		std::vector<maths::mat4> particle_matrices;
		std::vector<maths::vec3> particle_vertex_data;
	};
}