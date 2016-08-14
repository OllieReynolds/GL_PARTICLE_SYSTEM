#pragma once

#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "mat4.hpp"
#include "shader.hpp"
#include "utils.hpp"
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
		Text(int pixel_size = 24) : pixel_size(pixel_size) 
		{ 
		}

		void init_text();
		void draw_text(const std::string& msg, const maths::vec2f& position);
		void destroy_text();


	private:	
		GLuint vao;
		GLuint vbo;
		utils::Shader shader;

		int pixel_size;
		std::map<GLchar, Glyph> glyph_map;
	};
}