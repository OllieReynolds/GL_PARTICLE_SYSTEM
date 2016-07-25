#include "Shader.hpp"

namespace utils {
	Shader::Shader() {}

	Shader::Shader(const char* vertexSrc, const char* fragmentSrc) {
		std::ifstream vertexShaderFile(vertexSrc);
		std::ifstream fragmentShaderFile(fragmentSrc);

		std::stringstream vertexShaderStream, fragmentShaderStream;
		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();

		vertexShaderFile.close();
		fragmentShaderFile.close();

		std::string vertexCode = vertexShaderStream.str();
		std::string fragmentCode = fragmentShaderStream.str();

		const char* vCode = vertexCode.c_str();
		const char* fCode = fragmentCode.c_str();

		GLint status;
		GLchar infoLog[512];
		auto initShader = [&](GLuint shader, const char* src) {
			glShaderSource(shader, 1, &src, nullptr);
			glCompileShader(shader);
			glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
			if (!status) {
				glGetShaderInfoLog(shader, 512, nullptr, infoLog);
				std::cout << infoLog << std::endl;
			}
		};

		GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
		initShader(vertShader, vCode);

		GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		initShader(fragShader, fCode);

		program = glCreateProgram();

		glAttachShader(program, vertShader);
		glAttachShader(program, fragShader);

		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if (!status) {
			glGetProgramInfoLog(program, 512, nullptr, infoLog);
			std::cout << infoLog << std::endl;
		}

		use();
	}

	void Shader::use() {
		glUseProgram(program);
	}
}
