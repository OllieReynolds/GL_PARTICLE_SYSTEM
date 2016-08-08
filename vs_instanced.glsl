#version 450

struct Particle {
	vec3 position;
	vec3 scale;
	vec2 velocity;
	float mass;
};

layout(std430, binding = 0) buffer Particles {
	Particle particles[];
};

layout(std430, binding = 1) buffer ParticleMatrices {
	mat4 particle_matrices[];
};

layout(location = 0) in vec3 vp;

out float velocity_to_colour;

uniform mat4 proj;

void main () {
	int id = gl_InstanceID;
	gl_Position = proj * particle_matrices[id] * vec4(vp, 1.0);
	velocity_to_colour = length(particles[id].velocity);
};