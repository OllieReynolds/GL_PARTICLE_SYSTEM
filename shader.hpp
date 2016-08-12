#pragma once

#include <glew.h>
#include <iostream>
#include <iterator>
#include <fstream>

namespace utils {
	class Shader {
	public:
		Shader() { }
		Shader(const char* compute_shader_filename);
		Shader(const char* vertex_shader_filename, const char* fragment_shader_filename);

		void use();
		void destroy();

		GLint uniform_handle(const char* name);


	private:
		std::string load_source(const char* filename);
		void compile(GLuint shader, const char* src);
		void link();

		GLuint program;
	};
}
