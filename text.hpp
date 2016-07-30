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
		FT_Pos next_glyph_offset;
		
		maths::vec2i glyph_size;
		maths::vec2i bearing_offset;
	};

	class Text {
	public:
		Text(int pixel_size = 24, maths::vec2f position = {}) : 
			pixel_size(pixel_size),
			position(position) { }

		void init_text();
		void draw_text(const std::string& msg);
		void destroy_text();

		maths::vec2f position;

	private:
		GLuint vao;
		GLuint vbo;

		utils::Shader shader;

		int pixel_size;
		std::map<GLchar, Glyph> glyph_map;
	};
}