#version 450

in vec2 tex_coord;
out vec4 frag_colour;

uniform sampler2D tex0;

void main() {
	frag_colour = vec4(0.0, 0.0, 0.0, 0.0);//texture(tex0, tex_coord);
};