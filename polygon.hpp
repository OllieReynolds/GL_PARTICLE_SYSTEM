#pragma once

#include <glew.h>
#include <SOIL.h>

#include "globals.hpp"
#include "mat4.hpp"
#include "shader.hpp"
#include "utils.hpp"

namespace graphics {
	class Polygon {
	public:
		void init_polygon(const std::vector<maths::vec3>& vertices, const std::vector<maths::vec2f>& uvs, const maths::vec3 position, const maths::vec3 scale);
		void draw_polygon(GLenum mode);
		void destroy_polygon();

		void add_vertex(const maths::vec3& v);

	private:
		int num_vertices;
		int num_uvs;

		GLuint vao;
		GLuint vbo;
		GLuint uv_vbo;
		GLuint data;

		utils::Shader shader;
	};

}