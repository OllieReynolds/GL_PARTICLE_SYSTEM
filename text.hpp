#pragma once

#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "globals.hpp"
#include "mat4.hpp"
#include "shader.hpp"
#include "vec2.hpp"

namespace graphics {
	struct Glyph {
		GLuint data;
		GLuint next_glyph_offset;
		
		maths::vec2i glyph_size;
		maths::vec2i bearing_offset;
	};

	class Text {
	public:
		void init_text(int pixelSize);
		void draw_text(const std::string& msg, const maths::vec2f& pos);
		void destroy_text();


	private:

		GLuint vao;
		GLuint vbo;

		utils::Shader shader;

		std::map<GLchar, Glyph> glyph_map;
	};
}