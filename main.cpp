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

#include "simulation.hpp"

// Implement perlin noise?
GLFWwindow* setup_opengl();

int main() {
	GLFWwindow* window; 
	window = setup_opengl();

	simulation::Simulation simulation;
	simulation.init_simulation();

	glfwSetWindowUserPointer(window, &simulation);

	float frame_start_time, frame_end_time, frames_per_second = 0.f;

	while (!glfwWindowShouldClose(window)) {
		frame_start_time = utils::elapsed_time<float>();
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		simulation.update_simulation(window);
		simulation.draw_simulation(frames_per_second);
		glfwPollEvents();
		glfwSwapBuffers(window);

		frame_end_time = utils::elapsed_time<float>();
		frames_per_second = 1.f / (frame_end_time - frame_start_time);
	}

	simulation.destroy_simulation();
	glfwTerminate();
	return 0;
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	//simulation::Simulation* simulation = reinterpret_cast<simulation::Simulation*>(glfwGetWindowUserPointer(window));
	//simulation->mouse_position(maths::vec2f(xpos, ypos));
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		simulation::Simulation* simulation = reinterpret_cast<simulation::Simulation*>(glfwGetWindowUserPointer(window));
		simulation->on_kb_press(key);
	}
}

GLFWwindow* setup_opengl() {
	if (!glfwInit()) {
		std::cout << "GLFW failed to initialise" << std::endl;
		return NULL;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(
		static_cast<int>(utils::resolution()[0]), 
		static_cast<int>(utils::resolution()[1]),
		"Setting Up", 
		NULL, 
		NULL
	);
	if (!window) {
		std::cout << "GFLW failed to create window" << std::endl;
		glfwTerminate();
		return NULL;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cout << "Glew failed to initialise" << std::endl;
		std::cout << glewGetErrorString(err) << std::endl;
		glfwTerminate();
		return NULL;
	}

	GLenum err1 = GL_NO_ERROR;
	while ((err1 = glGetError()) != GL_NO_ERROR) {
		std::cout << err1 << std::endl;
	}

	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.314f, 0.314f, 0.314f, 0.0f);

	std::stringstream ss;
	ss << "Device Vendor: " << glGetString(GL_VENDOR) << std::endl;
	ss << "Device Renderer: " << glGetString(GL_RENDERER) << std::endl;
	ss << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	ss << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << ss.str();

	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);

	return window;
}