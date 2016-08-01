#include "particle_system.hpp"

namespace graphics {
	void ParticleSystem::update_particle_system() {
		static const float drag_intensity = 0.09f;
		static const float friction_intensity = 0.1f;
		static const float gravity_intensity = 0.1f;
		static const float wind_intensity = 1.f;

		for (size_t i = 0; i < particle_objects.size(); ++i) {
			apply_force(particle_objects[i],
				physics::calc_gravity(
					gravity_intensity, 
					{683, 384}, 1.f, 
					{particle_objects[i].position[0], particle_objects[i].position[1]}, particle_objects[i].mass
				)
			);

			update_particle(particle_objects[i]);
			particle_matrices[i].scale(particle_objects[i].scale).translate(particle_objects[i].position);
		}

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, matrix_vbo);
		glBufferSubData(
			GL_ARRAY_BUFFER,
			0,
			particle_matrices.size() * sizeof(maths::mat4),
			&particle_matrices[0]
		);
	}


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

		shader = utils::Shader(
			"vs_instanced.glsl",
			"fs_instanced.glsl"
		);

		glUniformMatrix4fv(
			glGetUniformLocation(shader.program, "proj"),
			1,
			GL_FALSE,
			&maths::orthographic_perspective(
				utils::resolution()[0],
				utils::resolution()[1],
				-1.f,
				1.f
			)[0][0]
		);
	}

	void ParticleSystem::constrain_particle(Particle& a) {
		const maths::vec3 offset = a.scale * 0.5f;

		for (size_t xy : {0, 1}) {
			if (a.position[xy] > utils::resolution()[xy] - offset[xy]) {
				a.position[xy] = utils::resolution()[xy] - offset[xy];
				a.velocity[xy] *= -1.f;
			} else if (a.position[xy] < offset[xy]) {
				a.position[xy] = offset[xy];
				a.velocity[xy] *= -1.f;
			}
		}
	}

	void ParticleSystem::update_particle(Particle& a) {
		a.velocity += a.acceleration;
		a.position += {a.velocity, 0.f};
		constrain_particle(a);
		a.acceleration = {0.f, 0.f};
	}
	void ParticleSystem::apply_force(Particle& a, const maths::vec2f& force) {
		a.acceleration += force / a.mass;
	}

	void ParticleSystem::draw_particle_system() {
		glBindVertexArray(vao);
		shader.use();
		glDrawArraysInstanced(GL_TRIANGLES, 0, 3, particle_objects.size());
	}

	void ParticleSystem::destroy_particle_system() {
		glDeleteProgram(shader.program);
		glDeleteBuffers(1, &position_vbo);
		glDeleteBuffers(1, &matrix_vbo);
		glDeleteVertexArrays(1, &vao);
	}
}