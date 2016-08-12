#version 450

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 velocity;
layout(location = 2) in float scale;
layout(location = 3) in float mass;

out float out_colour;

uniform mat4 proj;

void main() {
	int id = gl_InstanceID;
	gl_Position = proj * particle_matrices[id] * vec4(vp, 0.0, 1.0);
	out_colour = length(particles[id].velocity);
};