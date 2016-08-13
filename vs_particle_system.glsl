#version 450

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 velocity;
layout(location = 2) in float scale;
layout(location = 3) in float mass;

out float vertex_scale;
out float vertex_speed;

void main() {
	gl_Position = vec4(position, 0.0, 1.0);

	vertex_scale = scale;
	vertex_speed = length(velocity);
};