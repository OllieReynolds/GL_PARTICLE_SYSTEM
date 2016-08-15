#include "..\include\simulation.hpp"

namespace simulation {
	Simulation::Simulation() {
		particle_system = graphics::ParticleSystem(524288);
		text = graphics::Text(32);
		run_state = state::RUN;
	}

	void Simulation::init_simulation() {	
		particle_system.init_particle_system();
		text.init_text();	
	}

	void Simulation::update_simulation(GLFWwindow* window) {
		//if (run_state == state::RUN)
			//particle_system.update_particle_system();
	}

	void Simulation::draw_simulation(const float fps) {
		particle_system.draw_particle_system();

		static const maths::vec2f text_region_position = {0.f, utils::resolution[1] - 28.f};
		static const maths::vec2f text_region_offset = {0.f, 28.f};
		text.draw_text("FPS: " + std::to_string((int)fps), text_region_position);
		text.draw_text("Particles: 524,288", text_region_position - text_region_offset);
		switch (run_state) {
			case STOP: text.draw_text("State: STOP", text_region_position - (text_region_offset * 2.f)); break;
			case EDIT: text.draw_text("State: EDIT", text_region_position - (text_region_offset * 2.f)); break;
			case RUN:  text.draw_text("State: RUN",  text_region_position - (text_region_offset * 2.f)); break;
		}
	}

	void Simulation::destroy_simulation() {
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
