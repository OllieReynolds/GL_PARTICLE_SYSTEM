#pragma once

#include <sstream>
#include <iostream>

#include <glew.h>
#include <glfw3.h>

#include "globals.hpp"
#include "simulation.hpp"
#include "vec2.hpp"

namespace utils {
	GLFWwindow* setup_opengl();
}