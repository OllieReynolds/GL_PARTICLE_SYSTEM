#version 450

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 velocity;
layout(location = 2) in float scale;
layout(location = 3) in float mass;

out float vertex_colour;

void main() {
	gl_Position = vec4(vp, 0.0, 1.0);
	vertex_colour = length(velocity);
};