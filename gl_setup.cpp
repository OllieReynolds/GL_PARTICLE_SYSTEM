#include "gl_setup.hpp"

namespace utils {
	GLFWwindow* setup_opengl() {
		if (!glfwInit()) {
			std::cout << "GLFW failed to initialise" << std::endl;
			return NULL;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow* window = glfwCreateWindow(utils::resolution()[0], utils::resolution()[1], "Setting Up", NULL, NULL);
		if (!window) {
			std::cout << "GFLW failed to create window" << std::endl;
			glfwTerminate();
			return NULL;
		} else {
			glfwMakeContextCurrent(window);
			glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GL_FALSE);
			glfwSetMouseButtonCallback(window, simulation::mouse_button_callback);
		}

		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if (err != GLEW_OK) {
			std::cout << "Glew failed to initialise" << std::endl;
			std::cout << glewGetErrorString(err) << std::endl;
			glfwTerminate();
			return NULL;
		}

		//glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glClearColor(0.0, 0.0, 0.0, 0.0);

		std::stringstream ss;
		ss << "Device Vendor: " << glGetString(GL_VENDOR) << std::endl;
		ss << "Device Renderer: " << glGetString(GL_RENDERER) << std::endl;
		ss << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
		ss << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
		std::cout << ss.str();

		return window;
	}
}
