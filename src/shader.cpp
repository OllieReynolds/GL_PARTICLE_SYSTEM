#include "..\include\shader.hpp"

namespace utils {
	Shader::Shader(const char* compute_shader_filename) {
		GLuint computeShader = glCreateShader(GL_COMPUTE_SHADER);
		std::string src = load_source(compute_shader_filename);
		compile(computeShader, src.c_str());
		
		program = glCreateProgram();

		glAttachShader(program, computeShader);

		link();
		use();
	}

	Shader::Shader(const char* vertex_shader_filename, const char* fragment_shader_filename) {
		GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
		std::string v_src = load_source(vertex_shader_filename);
		compile(vertShader, v_src.c_str());

		GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		std::string f_src = load_source(fragment_shader_filename);
		compile(fragShader, f_src.c_str());

		program = glCreateProgram();

		glAttachShader(program, vertShader);
		glAttachShader(program, fragShader);

		link();
		use();
	}

	Shader::Shader(const char* vertex_shader_filename, const char* fragment_shader_filename, const char* geom_shader_filename) {
		GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
		std::string v_src = load_source(vertex_shader_filename);
		compile(vertShader, v_src.c_str());

		GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		std::string f_src = load_source(fragment_shader_filename);
		compile(fragShader, f_src.c_str());

		GLuint geomShader = glCreateShader(GL_GEOMETRY_SHADER);
		std::string g_src = load_source(geom_shader_filename);
		compile(geomShader, g_src.c_str());

		program = glCreateProgram();

		glAttachShader(program, vertShader);
		glAttachShader(program, fragShader);
		glAttachShader(program, geomShader);

		link();
		use();
	}

	void Shader::compile(GLuint shader, const char* src) {
		GLint status;
		GLchar infoLog[512];
		glShaderSource(shader, 1, &src, nullptr);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (!status) {
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			std::cout << infoLog << std::endl;
		}
	}

	void Shader::link() {
		GLint status;
		GLchar infoLog[512];
		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if (!status) {
			glGetProgramInfoLog(program, 512, nullptr, infoLog);
			std::cout << infoLog << std::endl;
		}
	}

	void Shader::use() {
		glUseProgram(program);
	}

	void Shader::destroy() {
		glDeleteProgram(program);
	}

	GLint Shader::uniform_handle(const char* name) {
		return glGetUniformLocation(program, name);
	}

	std::string Shader::load_source(const char* filename) {
		std::ifstream input{filename};
		return std::string{std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>()};
	}
}
