#include "particle_system.hpp"

namespace graphics {
	void ParticleSystem::init_particle_system() {
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &matrix_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, matrix_vbo);
		glBufferData(
			GL_ARRAY_BUFFER, 
			agents.size() * sizeof(maths::mat4),
			&transform_matrices[0], 
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
			vertices.size() * sizeof(maths::vec3), 
			&vertices[0], 
			GL_STATIC_DRAW
		);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(4);

		shader = utils::Shader(
			"vs_instanced.glsl", 
			"fs_instanced.glsl"
		);
		
		glUniformMatrix4fv(
			glGetUniformLocation(shader.program, "proj"),
			1,
			GL_FALSE,
			&maths::orthogonal_perspective(utils::resolution()[0], utils::resolution()[1], -1.f, 1.f)[0][0]
		);
	}

	void ParticleSystem::update_particle_system() {
		static const float drag_intensity = 0.009f;
		static const float friction_intensity = 0.1f;
		static const float gravity_intensity = 0.f;
		static const float wind_intensity = 10.f;

		for (int i = 0; i < agents.size(); ++i) {
			agents[i].apply_force(physics::calc_drag(drag_intensity, agents[i].velocity));
			agents[i].apply_force(physics::calc_gravity(gravity_intensity, agents[i].mass));
			agents[i].apply_force(physics::calc_wind(wind_intensity));
			//agents[i].apply_force(physics::calc_friction(friction_intensity, agents[i].velocity));

			agents[i].update();
			transform_matrices[i] = agents[i].model_matrix;
		}

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, matrix_vbo);
		glBufferSubData(
			GL_ARRAY_BUFFER,
			0,
			agents.size() * sizeof(maths::mat4),
			&transform_matrices[0]
		);
	}

	void ParticleSystem::draw_particle_system() {
		glBindVertexArray(vao);
		shader.use();
		glDrawArraysInstanced(GL_TRIANGLES, 0, 3, agents.size());
	}

	void ParticleSystem::destroy_particle_system() {
		glDeleteProgram(shader.program);
		glDeleteBuffers(1, &position_vbo);
		glDeleteBuffers(1, &matrix_vbo);
		glDeleteVertexArrays(1, &vao);
	}
}