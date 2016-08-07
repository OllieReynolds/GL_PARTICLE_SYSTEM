#include "particle_system.hpp"

namespace graphics {
	void ParticleSystem::init_particle_system() {
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &matrix_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, matrix_vbo);
		glBufferData(
			GL_ARRAY_BUFFER,
			particle_matrices.size() * sizeof(maths::mat4),
			&particle_matrices[0],
			GL_DYNAMIC_DRAW
		);

		for (int i : {0, 1, 2, 3}) {
			glVertexAttribPointer(
				i,
				4,
				GL_FLOAT,
				GL_FALSE,
				sizeof(maths::mat4),
				(GLvoid*)(sizeof(maths::vec4) * i)
			);
			glEnableVertexAttribArray(i);
			glVertexAttribDivisor(i, 1);
		}

		glGenBuffers(1, &position_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, position_vbo);
		glBufferData(
			GL_ARRAY_BUFFER,
			particle_vertex_data.size() * sizeof(maths::vec3),
			&particle_vertex_data[0],
			GL_STATIC_DRAW
		);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(4);

		glGenBuffers(1, &particle_ssbo);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, particle_ssbo);
		glBufferData(GL_SHADER_STORAGE_BUFFER, particle_objects.size() * sizeof(Particle), &particle_objects[0], GL_STATIC_DRAW);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particle_ssbo);

		render_shader = {
			"vs_instanced.glsl",
			"fs_instanced.glsl"
		};

		glUniformMatrix4fv(
			glGetUniformLocation(render_shader.program, "proj"),
			1,
			GL_FALSE,
			&maths::orthographic_perspective(
				utils::resolution()[0],
				utils::resolution()[1],
				-1.f,
				1.f
			)[0][0]
		);

		compute_shader = {
			"cs_particle_physics.glsl"
		};
	}

	void ParticleSystem::update_particle_system() {		
		glBindVertexArray(vao);

		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particle_ssbo);
		compute_shader.use();
		glDispatchCompute(256, 1, 1);
		glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

		Particle* ptr = (Particle*)glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);
		for (size_t i = 0; i < 65536; ++i)
			particle_matrices[i].scale(ptr[i].scale).translate(ptr[i].position);
		glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

		glBindBuffer(GL_ARRAY_BUFFER, matrix_vbo);
		glBufferSubData(
			GL_ARRAY_BUFFER,
			0,
			particle_matrices.size() * sizeof(maths::mat4),
			&particle_matrices[0]
		);
	}

	void ParticleSystem::draw_particle_system() {
		glBindVertexArray(vao);
		render_shader.use();
		glDrawArraysInstanced(GL_TRIANGLES, 0, 3, particle_objects.size());
	}

	void ParticleSystem::destroy_particle_system() {
		glDeleteProgram(compute_shader.program);
		glDeleteProgram(render_shader.program);
		glDeleteBuffers(1, &particle_ssbo);
		glDeleteBuffers(1, &position_vbo);
		glDeleteBuffers(1, &matrix_vbo);
		glDeleteVertexArrays(1, &vao);
	}
}