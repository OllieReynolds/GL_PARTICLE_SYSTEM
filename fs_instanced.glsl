#version 450

in float velocity_to_colour;

out vec4 frag_colour;

void main() {
	float v = velocity_to_colour * 0.3;
	frag_colour = vec4(v, 0.0, 1.0 - v, 0.1);
};