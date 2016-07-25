#include "particle_system.hpp"

namespace graphics {
	void ParticleSystem::init_particle_system(const std::vector<maths::vec3>& vertices) {
		delete[] agents;
		delete[] agent_transform_matrices;

		agents = new simulation::AutonomousAgent[num_particles];
		agent_transform_matrices = new maths::mat4[num_particles];

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &matrix_vbo);
		for (int i = 0; i < num_particles; ++i) {
			agents[i] = simulation::AutonomousAgent();
			agent_transform_matrices[i] = agents[i].model_matrix;
		}

		glBindBuffer(GL_ARRAY_BUFFER, matrix_vbo);
		glBufferData(
			GL_ARRAY_BUFFER, 
			num_particles * sizeof(maths::mat4), 
			agent_transform_matrices, 
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
		static const float dC = 0.009f;
		static const float fC = 0.1f;
		static const float gC = 0.f;
		static const float wC = 10.f;
		
		const maths::vec2f wind = physics::calc_wind(wC);

		for (int i = 0; i < num_particles; ++i) {
			agents[i].apply_force(physics::calc_drag(dC, agents[i].velocity));
			agents[i].apply_force(physics::calc_gravity(gC, agents[i].mass));
			agents[i].apply_force(wind);			
			//agents[i].apply_force(physics::calc_friction(fC, agents[i].velocity));

			agents[i].update();

			agent_transform_matrices[i] = agents[i].model_matrix;
		}

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, matrix_vbo);
		glBufferSubData(
			GL_ARRAY_BUFFER,
			0,
			num_particles * sizeof(maths::mat4),
			agent_transform_matrices
		);
	}

	void ParticleSystem::draw_particle_system() {
		glBindVertexArray(vao);
		shader.use();
		glDrawArraysInstanced(GL_TRIANGLES, 0, 3, num_particles);
	}

	void ParticleSystem::destroy_particle_system() {
		delete[] agents;
		delete[] agent_transform_matrices;

		glDeleteProgram(shader.program);
		glDeleteBuffers(1, &position_vbo);
		glDeleteBuffers(1, &matrix_vbo);
		glDeleteVertexArrays(1, &vao);
	}
}