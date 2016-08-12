#include "particle_system.hpp"

//todo: compare vector assign and filling one by one
namespace graphics {
	void ParticleSystem::init_particle_system() {
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		{ // Particle SSBO
			glGenBuffers(1, &particle_ssbo);
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, particle_ssbo);
			glBufferData(GL_SHADER_STORAGE_BUFFER, particles.size() * sizeof(Particle), &particles[0], GL_DYNAMIC_DRAW);
		}

		{ // Setup Vertex Attrib
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)(0));
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)(2 * sizeof(float)));
			glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)(1 * sizeof(float)));
			glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)(1 * sizeof(float)));
		}

		{ // Shaders
			compute_shader = {
				"cs_particle_system.glsl"
			};

			render_shader = {
				"vs_particle_system.glsl",
				"fs_particle_system.glsl"
			};

			glUniformMatrix4fv(render_shader.uniform_handle("proj"), 1, GL_FALSE, &maths::orthographic_perspective(utils::resolution[0], utils::resolution[1], -1.f, 1.f)[0][0]);
		}	
	}

	void ParticleSystem::draw_particle_system() {
		{ // Invoke Compute Shader and wait for all memory access to SSBO to safely finish
			compute_shader.use();
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particle_ssbo);
			glDispatchCompute(128, 1, 1);
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