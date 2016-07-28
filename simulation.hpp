#pragma once

#include <glew.h>
#include <glfw3.h>

#include "autonomous_agent.hpp"
#include "forces.hpp"
#include "particle_system.hpp"
#include "polygon.hpp"
#include "text.hpp"
#include "vec3.hpp"


namespace simulation {
	enum state {
		READY,
		PAUSED,
		EDITING
	};

	class Simulation {
	public:
		Simulation();

		void init_simulation();
		void update_simulation(GLFWwindow* window);
		void draw_simulation(const float fps);
		void destroy_simulation();

		void mouse_position(const maths::vec2f& position);

	private:
		maths::vec2f mouse_coords;

		graphics::ParticleSystem particle_system;

		graphics::Polygon polygon_simple;
		graphics::Polygon polygon_texture;
		
		graphics::Text text;

		state run_state;
	};
}