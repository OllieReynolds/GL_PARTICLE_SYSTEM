#include "..\include\particle_system.hpp"

//todo: compare vector assign and filling one by one
namespace graphics {
	void ParticleSystem::init_particle_system() {
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		{ // Particle SSBO
			glGenBuffers(1, &particle_ssbo);
			glBindBuffer(GL_ARRAY_BUFFER, particle_ssbo);
			glBufferData(GL_ARRAY_BUFFER, particles.size() * sizeof(Particle), &particles[0], GL_STATIC_DRAW);
		}


		{ // Setup Vertex Attributes
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
			glEnableVertexAttribArray(3);

			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), 0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)(sizeof(float) * 2));
			glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)(sizeof(float) * 4));
			glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)(sizeof(float) * 5));

			glVertexAttribDivisor(0, 1);
			glVertexAttribDivisor(1, 1);
			glVertexAttribDivisor(2, 1);
			glVertexAttribDivisor(3, 1);
		}

		glBindVertexArray(0);

		{ // Shaders
			compute_shader = {
				"shaders/particle_system.c.glsl"
			};

			glUniform1f(compute_shader.uniform_handle("time"), utils::elapsed_time<float>());

			render_shader = {
				"shaders/particle_system.v.glsl",
				"shaders/particle_system.f.glsl",
				"shaders/particle_system.g.glsl"
			};

			glUniformMatrix4fv(render_shader.uniform_handle("projection"), 1, GL_FALSE, &maths::orthographic_perspective(utils::resolution[0], utils::resolution[1], -1.f, 1.f)[0][0]);
		}	
	}

	void ParticleSystem::draw_particle_system() {
		{ // Invoke Compute Shader and wait for all memory access to SSBO to safely finish
			compute_shader.use();
			glUniform1f(compute_shader.uniform_handle("time"), utils::elapsed_time<float>());
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particle_ssbo);
			glDispatchCompute((particles.size() / 128)+1, 1, 1);
			glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);
		}

		{ // Render the results
			render_shader.use();
			glBindVertexArray(vao);
			glDrawArraysInstanced(GL_POINTS, 0, 1, particles.size());
			glBindVertexArray(0);
		}
		
	}

	void ParticleSystem::destroy_particle_system() {
		render_shader.destroy();
		compute_shader.destroy();
		glDeleteBuffers(1, &particle_ssbo);
		glDeleteVertexArrays(1, &vao);
	}

	std::string ParticleSystem::print_compute_shader_info() {
		std::stringstream ss;
		ss << "Compute Shader Capabilities:" << std::endl;
		ss << "GL_MAX_COMPUTE_WORK_GROUP_COUNT:" << std::endl;
		for (int i : {0, 1, 2}) {
			int tmp = 0;
			glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, i, &tmp);
			ss << tmp << std::endl;
		}

		ss << "GL_MAX_COMPUTE_WORK_GROUP_SIZE:" << std::endl;
		for (int i : {0, 1, 2}) {
			int tmp = 0;
			glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, i, &tmp);
			ss << tmp << std::endl;
		}

		return ss.str();
	}
}
