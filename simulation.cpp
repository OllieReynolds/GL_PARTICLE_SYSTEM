#include "simulation.hpp"

namespace simulation {

	Simulation::Simulation() {
		polygon_simple = graphics::Polygon(
			{  // Vertices
			    {-1.f, -1.f, -1.f},
				{ 1.f, -1.f, -1.f},
				{ 0.f,  1.f, -1.f}
			},
			{  // 404 - UVs not found
			
			}, // Position & Scale 
			{utils::resolution()[0] * 0.5f, utils::resolution()[1] * 0.5f, -1.f},
			{utils::resolution()[0] * 0.3f, utils::resolution()[1] * 0.3f,  0.f}
		);

		polygon_texture = graphics::Polygon(
		    {  // Vertices
				{-0.5, -0.5, -1.0},
				{ 0.5, -0.5, -1.0},
				{ 0.5,  0.5, -1.0},
				{ 0.5,  0.5, -1.0},
				{-0.5,  0.5, -1.0},
				{-0.5, -0.5, -1.0}
		    },
			{  // UVs
				{0.0, 0.0},
				{1.0, 0.0},
				{1.0, 1.0},
				{1.0, 1.0},
				{0.0, 1.0},
				{0.0, 0.0}
			}, // Position & Scale 
			{300.f, 300.f, -1.f}, 
			{256.f, 256.f,  0.f}
		);

		particle_system = graphics::ParticleSystem(
			30, 
			{   // Vertices
				{ 0.0,  0.5, 0.0},
				{ 0.5, -0.5, 0.0},
				{-0.5, -0.5, 0.0}
			}
		);

		run_state = READY;
	}

	void Simulation::init_simulation() {		
		polygon_simple.init_polygon();
		polygon_texture.init_polygon();
		particle_system.init_particle_system();
		text.init_text(32.f);	
	}

	void Simulation::update_simulation(GLFWwindow* window) {
		// Move this to the game dev stack exchange input link
		if      (glfwGetKey(window, GLFW_KEY_P)) run_state = state::PAUSED;
		else if (glfwGetKey(window, GLFW_KEY_E)) run_state = state::EDITING;
		else if (glfwGetKey(window, GLFW_KEY_R)) run_state = state::READY;

		if (run_state == READY)
			particle_system.update_particle_system();
	}

	void Simulation::draw_simulation(const float fps) {
		particle_system.draw_particle_system();

		polygon_simple.draw_polygon(GL_LINE_LOOP);
		polygon_texture.draw_polygon(GL_TRIANGLES);

		text.draw_text("FPS: " + std::to_string((int)fps), {0.f, 740.f});
		text.draw_text("Particles: " + std::to_string(particle_system.size()), {0.f, 710.f});

		switch (run_state) {
			case PAUSED:   text.draw_text("State: PAUSED", {0.f, 680.f}); break;
			case EDITING:  text.draw_text("State: EDITING", {0.f, 680.f}); break;
			case READY: text.draw_text("State: READY", {0.f, 680.f}); break;
		}
	}

	void Simulation::destroy_simulation() {
		particle_system.destroy_particle_system();
		polygon_simple.destroy_polygon();
		polygon_texture.destroy_polygon();
		text.destroy_text();
	}

	// Mouse position uses NDC
	void Simulation::mouse_position(const maths::vec2f& position) {
		mouse_coords = position;
	}
}