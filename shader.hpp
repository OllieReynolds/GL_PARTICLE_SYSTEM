#pragma once

#include <glew.h>
#include <iostream>
#include <fstream>
#include <sstream>

namespace utils {
	class Shader {
	public:
		Shader();
		Shader(const char* vertexSrc, const char* fragmentSrc);

		void use();

		GLuint program;
	};
}
