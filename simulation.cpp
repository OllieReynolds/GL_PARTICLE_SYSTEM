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

		text = graphics::Text(
			32,
		    {0.f, 680.f}
		);

		run_state = state::RUN;
	}

	void Simulation::init_simulation() {		
		polygon_simple.init_polygon();
		polygon_texture.init_polygon();
		particle_system.init_particle_system();
		text.init_text();	
	}

	void Simulation::update_simulation(GLFWwindow* window) {
		if (run_state == state::RUN)
			particle_system.update_particle_system();
	}

	void Simulation::draw_simulation(const float fps) {
		particle_system.draw_particle_system();

		polygon_simple.draw_polygon(GL_LINE_LOOP);
		polygon_texture.draw_polygon(GL_TRIANGLES);

		text.position = {0.f, 740.f};
		text.draw_text("FPS: " + std::to_string((int)fps));
		text.position = {0.f, 710.f};
		text.draw_text("Particles: " + std::to_string(particle_system.size()));

		text.position = {0.f, 680.f};
		switch (run_state) {
			case STOP: text.draw_text("State: STOP"); break;
			case EDIT: text.draw_text("State: EDIT"); break;
			case RUN:  text.draw_text("State: RUN"); break;
		}
	}

	void Simulation::destroy_simulation() {
		particle_system.destroy_particle_system();
		polygon_simple.destroy_polygon();
		polygon_texture.destroy_polygon();
		text.destroy_text();
	}

	// Mouse position uses Normalised Device Coords
	void Simulation::mouse_position(const maths::vec2f& position) {
		mouse_coords = position;
	}

	void Simulation::on_kb_press(int key) {
		switch (key) {
			case GLFW_KEY_S: run_state = state::STOP; break;
			case GLFW_KEY_E: run_state = state::EDIT; break;
			case GLFW_KEY_R: run_state = state::RUN;  break;
		}
	}
}