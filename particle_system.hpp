#pragma once

#include "forces.hpp"
#include "shader.hpp"
#include "mat4.hpp"

namespace graphics {
	struct Particle {
		Particle() : 
			position(utils::gen_random(0.f, utils::resolution[0]), utils::gen_random(0.f, utils::resolution[1])),
			scale(utils::gen_random(2.f, 22.f)), mass(scale), velocity(0.f) 
		{ 
		}

		maths::vec2f position;
		maths::vec2f velocity;
		float scale;
		float mass;
	};

	class ParticleSystem {
	public:
		ParticleSystem(int num_particles = 10, const std::vector<maths::vec3>& vertices = {});

		void init_particle_system();
		void update_particle_system();
		void draw_particle_system();
		void destroy_particle_system();

		std::string print_compute_shader_info();


	private:
		GLuint vao;
		GLuint vertex_vbo;
		GLuint particle_ssbo;
		GLuint matrix_ssbo;

		utils::Shader compute_shader;
		utils::Shader render_shader;
		
		std::vector<Particle>    particle_objects;
		std::vector<maths::mat4> particle_matrices;
		std::vector<maths::vec3> particle_vertex_data;
	};
}