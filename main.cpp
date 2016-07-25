#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "SOIL.lib")
#pragma comment(lib, "freetype265MT.lib")

#include "gl_setup.hpp"
#include "simulation.hpp"

int main() {
	GLFWwindow* window; 
	window = utils::setup_opengl();

	simulation::Simulation simulation;
	simulation.init_simulation();

	float frame_start_time = 0.f;
	float frame_end_time = 0.f;
	float frames_per_second = 0.f;

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