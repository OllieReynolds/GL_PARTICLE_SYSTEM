#include "polygon.hpp"

namespace graphics {
	void Polygon::init_polygon() {
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(
			GL_ARRAY_BUFFER, 
			vertices.size() * sizeof(maths::vec3),
			&vertices[0],
			GL_STATIC_DRAW
		);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
;
		if (!uvs.empty()) {
			glGenBuffers(1, &uv_vbo);
			glBindBuffer(GL_ARRAY_BUFFER, uv_vbo);
			glBufferData(
				GL_ARRAY_BUFFER,
				uvs.size() * sizeof(maths::vec2f),
				&uvs[0],
				GL_STATIC_DRAW
			);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(1);

			glGenTextures(1, &tex_data);
			glBindTexture(GL_TEXTURE_2D, tex_data);

			int width;
			int height;
			unsigned char* image = SOIL_load_image("uv.jpg", &width, &height, 0, SOIL_LOAD_AUTO);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(GL_TEXTURE_2D);

			SOIL_free_image_data(image);
			glBindTexture(GL_TEXTURE_2D, 0);

			shader = utils::Shader("vs_texture.glsl", "fs_texture.glsl");
		} else {
			shader = utils::Shader("vs_default.glsl", "fs_default.glsl");
		}

		glUniformMatrix4fv(
			//glGetUniformLocation(shader.program, "proj"),
			shader.uniform_handle("proj"),
			1,
			GL_FALSE,
			&maths::orthographic_perspective(
				utils::resolution[0],
				utils::resolution[1],
				-1.f, 
				1.f
			)[0][0]
		);

		glUniformMatrix4fv(
			//glGetUniformLocation(shader.program, "model"),
			shader.uniform_handle("model"),
			1,
			GL_FALSE,
			&maths::mat4().scale(scale).translate(position)[0][0]
		);
	}

	void Polygon::draw_polygon(GLenum mode) {
		shader.use();

		if (!uvs.empty()) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tex_data);
			//glUniform1i(glGetUniformLocation(shader.program, "tex0"), 0);
			glUniform1i(shader.uniform_handle("tex0"), 0);
		}

		glBindVertexArray(vao);
		glDrawArrays(mode, 0, vertices.size());
		glBindVertexArray(0);
	}

	void Polygon::destroy_polygon() {
		shader.destroy();
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);

		if (!uvs.empty())
			glDeleteTextures(1, &tex_data);
	}
}