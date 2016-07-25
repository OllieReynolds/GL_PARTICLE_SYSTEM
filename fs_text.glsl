#version 450

in vec2 tex_coord;
out vec4 frag_colour;

uniform sampler2D tex0;
uniform vec3 colour;

void main() {
	vec4 c = vec4(1.0, 1.0, 1.0, texture(tex0, tex_coord).r);
	frag_colour = c * vec4(colour, 1.0);
};