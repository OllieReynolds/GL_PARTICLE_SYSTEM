#include "simulation.hpp"

namespace simulation {
	void Simulation::init_simulation() {
		text.init_text(32.f);
		
		std::vector<maths::vec3> particle_system_instance_vertices = {
			{0.0, 0.5, 0.0},
		    {0.5, -0.5, 0.0},
			{-0.5, -0.5, 0.0}
	 	    
		};
		particle_system.init_particle_system(particle_system_instance_vertices);

		std::vector<maths::vec3> polygon_vertices = {
			{-1.f, -1.f, -1.f},
			{ 1.f, -1.f, -1.f},
			{ 0.f,  1.f, -1.f}
		};
		maths::vec3 polygon_position = {utils::resolution()[0] * 0.5f, utils::resolution()[1] * 0.5f, -1.f};
		maths::vec3 polygon_scale = {utils::resolution()[0] * 0.3f, utils::resolution()[1] * 0.3f, 0.f};
		polygon_simple.init_polygon(polygon_vertices, {}, polygon_position, polygon_scale);
		
		std::vector<maths::vec3> texture_vertices = {
			{-0.5, -0.5, -1.0},
		    { 0.5, -0.5, -1.0},
		    { 0.5,  0.5, -1.0},
			{ 0.5,  0.5, -1.0},
			{-0.5,  0.5, -1.0},
			{-0.5, -0.5, -1.0}
		};
		std::vector<maths::vec2f> texture_uvs = {
			{0.0, 0.0},
			{1.0, 0.0},
			{1.0, 1.0},
			{1.0, 1.0},
			{0.0, 1.0},
			{0.0, 0.0}
		};
		maths::vec3 texture_position = {300.f, 300.f, -1.f};
		maths::vec3 texture_scale = {256.f, 256.f, 0.f};
		polygon_texture.init_polygon(texture_vertices, texture_uvs, texture_position, texture_scale);

		run_state = UPDATING;
	}

	void Simulation::update_simulation(GLFWwindow* window) {
		if      (glfwGetKey(window, GLFW_KEY_P)) run_state = state::PAUSED;
		else if (glfwGetKey(window, GLFW_KEY_U)) run_state = state::UPDATING;
		else if (glfwGetKey(window, GLFW_KEY_E)) run_state = state::EDITING;

		switch (run_state) {
		case UPDATING:
			particle_system.update_particle_system();
			break;

		case PAUSED:
			break;

		case EDITING:
			break;
		}
	}

	void Simulation::draw_simulation(const float fps) {
		switch (run_state) {
		case UPDATING:
			particle_system.draw_particle_system();
			polygon_simple.draw_polygon(GL_LINE_LOOP);
			polygon_texture.draw_polygon(GL_TRIANGLES);
			text.draw_text("FPS: " + std::to_string((int)fps), {0.f, 740.f});
			text.draw_text("Particles: " + std::to_string(particle_system.num_particles), {0.f, 710.f});
			text.draw_text("State: UPDATING", {0.f, 680.f});
			break;

		case PAUSED:
			particle_system.draw_particle_system();
			polygon_simple.draw_polygon(GL_LINE_LOOP);
			polygon_texture.draw_polygon(GL_TRIANGLES);
			text.draw_text("FPS: " + std::to_string((int)fps), {0.f, 740.f});
			text.draw_text("Particles: " + std::to_string(particle_system.num_particles), {0.f, 710.f});
			text.draw_text("State: PAUSED", {0.f, 680.f});
			break;

		case EDITING:
			polygon_simple.draw_polygon(GL_LINE_LOOP);
			text.draw_text("FPS: " + std::to_string((int)fps), {0.f, 740.f});
			text.draw_text("Particles: " + std::to_string(particle_system.num_particles), {0.f, 710.f});
			text.draw_text("State: EDITING", {0.f, 680.f});
			break;
		}
		
	}

	void Simulation::destroy_simulation() {
		particle_system.destroy_particle_system();
		polygon_simple.destroy_polygon();
		polygon_texture.destroy_polygon();
		text.destroy_text();
	}
}