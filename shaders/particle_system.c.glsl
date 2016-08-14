#version 450

struct Particle {
	vec2 position;
	vec2 velocity;
	float scale;
	float mass;
};

layout(std430, binding = 0) buffer Particles {
	Particle particles[];
};

layout(local_size_x = 128) in;

uniform float time;
uniform vec2 resolution;
uniform vec2 attractor_radii;

void check_boundaries(uint gid) {
	if (particles[gid].position.x > resolution.x) {
		particles[gid].position.x = resolution.x;
		particles[gid].velocity.x *= -1;
	}
	else if (particles[gid].position.x < 0) {
		particles[gid].position.x = 0;
		particles[gid].velocity.x *= -1;
	}

	if (particles[gid].position.y > resolution.y) {
		particles[gid].position.y = resolution.y;
		particles[gid].velocity.y *= -1;
	}
	else if (particles[gid].position.y < 0) {
		particles[gid].position.y = 0;
		particles[gid].velocity.y *= -1;
	}
}

vec2 calculate_gravity(uint gid, float attractor_mass, vec2 attractor_location) {
	float d = distance(attractor_location, particles[gid].position);
	float m = (attractor_mass * particles[gid].mass) / d;
	return (attractor_location - particles[gid].position) * m;
}

void main() {
	uint gid = gl_GlobalInvocationID.x;
	
	// Attractor position and offset
	vec2 p = 0.5 * resolution;
	vec2 a = vec2(cos(time), sin(time)) * attractor_radii;

	// Attractor #1
	vec2 g1 = calculate_gravity(gid, 0.0001, p + a);
	particles[gid].velocity += g1 * particles[gid].mass;

	// Attractor #2
	vec2 g2 = calculate_gravity(gid, 0.0001, p - a);
	particles[gid].velocity += g2 * particles[gid].mass;

	// Update position from velocity
	particles[gid].position += particles[gid].velocity;

	//check_boundaries(gid);
}
