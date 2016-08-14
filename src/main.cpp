#ifdef _DEBUG
	#pragma comment(lib, "glew32.lib")
	#pragma comment(lib, "glfw3.lib")
	#pragma comment(lib, "opengl32.lib")
	#pragma comment(lib, "SOIL.lib")
	#pragma comment(lib, "freetype265MTd.lib")
#else
	#pragma comment(lib, "glew32.lib")
	#pragma comment(lib, "glfw3.lib")
	#pragma comment(lib, "opengl32.lib")
	#pragma comment(lib, "SOIL.lib")
	#pragma comment(lib, "freetype265MT.lib")
#endif

#include "..\include\simulation.hpp"

namespace {
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
		//simulation::Simulation* simulation = reinterpret_cast<simulation::Simulation*>(glfwGetWindowUserPointer(window));
		//simulation->mouse_position(maths::vec2f(xpos, ypos));
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (action == GLFW_PRESS) {
			simulation::Simulation* simulation = reinterpret_cast<simulation::Simulation*>(glfwGetWindowUserPointer(window));
			simulation->on_kb_press(key);
		}
	}

	enum setup_result {
		SUCCESS,
		FAILURE
	};

	struct setup_status {
		setup_result code;
		std::string msg;
		GLFWwindow* window;
	};

	setup_status setup() {
		// GLFW Init
		if (!glfwInit()) 
			return {setup_result::FAILURE, "GLFW failed to initialise", nullptr};

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow* window = glfwCreateWindow(
			static_cast<int>(utils::resolution[0]), static_cast<int>(utils::resolution[1]),
			"Particle Simulation",
			NULL, NULL
		);

		if (!window) {
			glfwTerminate();
			return {setup_result::FAILURE, "GFLW failed to create window", nullptr};
		}

		glfwSetKeyCallback(window, key_callback);
		glfwSetCursorPosCallback(window, cursor_position_callback);
		glfwMakeContextCurrent(window);

		// Glew Init
		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if (err != GLEW_OK) {
			glfwTerminate();
			return {setup_result::FAILURE, "Glew failed to initialise", nullptr};
		}
	
		// GL Config
		glEnable(GL_BLEND);
		glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);


		glClearColor(0.f, 0.f, 0.f, 0.f);

		glGetError();
	
		return {
			setup_result::SUCCESS,
			[]() -> std::string {
				std::stringstream ss;
				ss << "Device Vendor: "   << glGetString(GL_VENDOR)                   << std::endl;
				ss << "Device Renderer: " << glGetString(GL_RENDERER)                 << std::endl;
				ss << "OpenGL Version: "  << glGetString(GL_VERSION)                  << std::endl;
				ss << "GLSL Version: "    << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
				return ss.str();
			}(),
			window
		};
	}

	bool check_running(GLFWwindow* window, int duration) {
		return !glfwWindowShouldClose(window) && utils::elapsed_time<float>() < duration;
	}
}

int main() {
	// Init
	setup_status status = setup();
	if (status.code != setup_result::SUCCESS)
		return -1;

	simulation::Simulation simulation;
	simulation.init_simulation();

	glfwSetWindowUserPointer(status.window, &simulation);

	float frame_end_time, frames_per_second = 0.f;
	float frame_start_time = utils::elapsed_time<float>();

	// Run until Esc. pressed or N seconds elapsed
	while (check_running(status.window, INT_MAX)) {
		{ // Per-frame updating and drawing here
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			simulation.update_simulation(status.window);
			simulation.draw_simulation(frames_per_second);
			glfwPollEvents();
			glfwSwapBuffers(status.window);
		}

		{ // Frame metrics and logging here
			frame_end_time = utils::elapsed_time<float>();
			frames_per_second = 1.f / (frame_end_time - frame_start_time);
			frame_start_time = utils::elapsed_time<float>();
		}
	}

	// Quit
	simulation.destroy_simulation();
	glfwTerminate();
	return 0;
}
