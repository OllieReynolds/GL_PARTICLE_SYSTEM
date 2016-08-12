#include "particle_system.hpp"

//todo: compare vector assign and filling one by one
namespace graphics {
	ParticleSystem::ParticleSystem(int num_particles, const std::vector<maths::vec3>& vertices) :
		particle_vertex_data(vertices),
		particle_objects(),
		particle_matrices()
	{
		for (int i = 0; i < num_particles; ++i) {
			particle_objects.push_back(Particle());
			particle_matrices.push_back(maths::mat4());
		}
	}

	void ParticleSystem::init_particle_system() {
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		{ // Matrix SSBO
			glGenBuffers(1, &matrix_ssbo);
			glBindBuffer(GL_ARRAY_BUFFER, matrix_ssbo);
			GLsizeiptr sz = particle_matrices.size() * sizeof(maths::mat4);
			glBufferData(GL_ARRAY_BUFFER, sz, &particle_matrices[0], GL_DYNAMIC_DRAW);
		}
		

		{ // Vertex VBO
			glGenBuffers(1, &vertex_vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
			GLsizeiptr sz = particle_matrices.size() * sizeof(Particle);
			glBufferData(GL_ARRAY_BUFFER, sz, &particle_vertex_data[0], GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
			glEnableVertexAttribArray(0);
		}

		{ // Particle SSBO
			glGenBuffers(1, &particle_ssbo);
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, particle_ssbo);
			GLsizeiptr sz = particle_matrices.size() * sizeof(Particle);
			glBufferData(GL_SHADER_STORAGE_BUFFER, sz, &particle_objects[0], GL_DYNAMIC_DRAW);
		}

		
		{ // Shaders
			render_shader = {
				"vs_instanced.glsl",
				"fs_instanced.glsl"
			};

			glUniformMatrix4fv(
				//glGetUniformLocation(render_shader.program, "proj"),
				render_shader.uniform_handle("proj"),
				1,
				GL_FALSE,
				&maths::orthographic_perspective(
					utils::resolution[0],
					utils::resolution[1],
					-1.f,
					1.f
				)[0][0]
			);

			compute_shader = {
				"cs_particle_physics.glsl"
			};
		}	

		print_compute_shader_info();
	}

	void ParticleSystem::update_particle_system() {		
		glBindVertexArray(vao);

		{ // Invoke Compute Shader and wait for all memory access to SSBO to safely finish
			compute_shader.use();
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particle_ssbo);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, matrix_ssbo);
			glDispatchCompute(128, 1, 1);
			glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
		}
		
		{ // Sync client side memory with Compute Shader
			{ // Particle SSBO
				glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particle_ssbo);
				Particle* ptr = (Particle*)glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);
				particle_objects.assign(ptr, ptr + particle_objects.size());
				glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
			}

			{ // Matrix SSBO
				glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, matrix_ssbo);
				maths::mat4* ptr = (maths::mat4*)glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);
				particle_matrices.assign(ptr, ptr + particle_matrices.size());
				glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
			}	
		}
	}

	void ParticleSystem::draw_particle_system() {
		glBindVertexArray(vao);
		render_shader.use();
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particle_ssbo);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, matrix_ssbo);
		glDrawArraysInstanced(GL_TRIANGLES, 0, 3, particle_objects.size());
	}

	void ParticleSystem::destroy_particle_system() {
		render_shader.destroy();
		compute_shader.destroy();
		glDeleteBuffers(1, &particle_ssbo);
		glDeleteBuffers(1, &vertex_vbo);
		glDeleteBuffers(1, &matrix_ssbo);
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