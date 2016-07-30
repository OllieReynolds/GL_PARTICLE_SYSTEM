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
		Polygon(
			const std::vector<maths::vec3>& vertices = {}, const std::vector<maths::vec2f>& uvs = {},
			const maths::vec3 position = {}, const maths::vec3 scale = {}) :
			vertices(vertices), uvs(uvs),
			position(position), scale(scale) { }

		void init_polygon();
		void draw_polygon(GLenum mode);
		void destroy_polygon();
		
		void add_vertex(const maths::vec3& v);

	private:

		std::vector<maths::vec2f> uvs;
		std::vector<maths::vec3> vertices;

		maths::vec3 position;
		maths::vec3 scale;

		GLuint vao;
		
		GLuint vbo;
		GLuint uv_vbo;

		GLuint tex_data;

		utils::Shader shader;
	};

}