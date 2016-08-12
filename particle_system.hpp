#pragma once

#include "forces.hpp"
#include "shader.hpp"
#include "mat4.hpp"

namespace graphics {
	struct Particle {
		Particle() : 
			position(utils::gen_random(0.f, utils::resolution[0]), utils::gen_random(0.f, utils::resolution[1])),
			velocity(0.f),
			scale(utils::gen_random(2.f, 22.f)), 
			mass(scale)
		{  
		}

		maths::vec2f position;
		maths::vec2f velocity;
		float scale;
		float mass;
	};


	class ParticleSystem {
	public:
		ParticleSystem(int num_particles) : particles() 
		{
			for (int i = 0; i < num_particles; ++i) {
				particles.push_back(Particle());
			}
		}

		void init_particle_system();
		void draw_particle_system();
		void destroy_particle_system();

		std::string print_compute_shader_info();


	private:
		GLuint vao;
		GLuint particle_ssbo;

		utils::Shader compute_shader;
		utils::Shader render_shader;
		
		std::vector<Particle> particles;
	};
}