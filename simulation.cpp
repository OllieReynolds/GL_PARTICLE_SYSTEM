#include "simulation.hpp"

namespace simulation {

	Simulation::Simulation() {
		//polygon_simple = graphics::Polygon(
		//	{  // Vertices
		//	    {-1.f, -1.f, -1.f},
		//		{ 1.f, -1.f, -1.f},
		//		{ 0.f,  1.f, -1.f}
		//	},
		//	{  // 404 - UVs not found
		//	
		//	}, // Position & Scale 
		//	{utils::resolution()[0] * 0.5f, utils::resolution()[1] * 0.5f, -1.f},
		//	{utils::resolution()[0] * 0.3f, utils::resolution()[1] * 0.3f,  0.f}
		//);

		//polygon_texture = graphics::Polygon(
		//    {  // Vertices
		//		{-0.5, -0.5, -1.0},
		//		{ 0.5, -0.5, -1.0},
		//		{ 0.5,  0.5, -1.0},
		//		{ 0.5,  0.5, -1.0},
		//		{-0.5,  0.5, -1.0},
		//		{-0.5, -0.5, -1.0}
		//    },
		//	{  // UVs
		//		{0.0, 0.0},
		//		{1.0, 0.0},
		//		{1.0, 1.0},
		//		{1.0, 1.0},
		//		{0.0, 1.0},
		//		{0.0, 0.0}
		//	}, // Position & Scale 
		//	{300.f, 300.f, -0.f}, 
		//	{256.f, 256.f,  0.f}
		//);

		particle_system = graphics::ParticleSystem(
			65536,
			{   // Vertices
				{ 0.0,  0.5, 0.0},
				{ 0.5, -0.5, 0.0},
				{-0.5, -0.5, 0.0}
			}
		);
		std::cout << particle_system.print_compute_shader_info() << std::endl;

		text = graphics::Text(32);

		run_state = state::RUN;
	}

	void Simulation::init_simulation() {	
		/*polygon_texture.init_polygon();
		polygon_simple.init_polygon();*/
		particle_system.init_particle_system();
		text.init_text();	
	}

	void Simulation::update_simulation(GLFWwindow* window) {
		//if (run_state == state::RUN)
			//particle_system.update_particle_system();
	}

	void Simulation::draw_simulation(const float fps) {
		/*polygon_texture.draw_polygon(GL_TRIANGLES);
		polygon_simple.draw_polygon(GL_LINE_LOOP);*/
		
		particle_system.draw_particle_system();

		text.draw_text("FPS: "       + std::to_string((int)fps), {0.f, 740.f});
		text.draw_text("Particles: " + std::to_string(65536),    {0.f, 710.f});
		switch (run_state) {
			case STOP: text.draw_text("State: STOP", {0.f, 680.f}); break;
			case EDIT: text.draw_text("State: EDIT", {0.f, 680.f}); break;
			case RUN:  text.draw_text("State: RUN", {0.f, 680.f}); break;
		}
	}

	void Simulation::destroy_simulation() {
		/*polygon_texture.destroy_polygon();
		polygon_simple.destroy_polygon();*/
		particle_system.destroy_particle_system();
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