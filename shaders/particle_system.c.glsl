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

void check_boundaries(uint gid) {
	float offset = particles[gid].scale * 0.5;
	float t = 1280.0 - offset;
	float r = 720.0 - offset;

	if (particles[gid].position.x > r) {
		particles[gid].position.x = r;
		particles[gid].velocity.x *= -1;
	}
	else if (particles[gid].position.x < offset) {
		particles[gid].position.x = offset;
		particles[gid].velocity.x *= -1;
	}

	if (particles[gid].position.y > t) {
		particles[gid].position.y = t;
		particles[gid].velocity.y *= -1;
	}
	else if (particles[gid].position.y < offset) {
		particles[gid].position.y = offset;
		particles[gid].velocity.y *= -1;
	}
}

vec2 calculate_gravity(uint gid, float attractor_mass, vec2 attractor_location) {
	float d = distance(attractor_location, particles[gid].position);
	float m = (attractor_mass * particles[gid].mass) / d;
	return (attractor_location - particles[gid].position) * m;
}

void apply_forces(uint gid) {
	vec2 s = vec2(320.0, 180.0);
	vec2 r = vec2(100.0, 100.0);
	vec2 p = vec2(r.x * cos(time), r.y * sin(time)) + r + s;
	vec2 g = calculate_gravity(gid, 0.0001, p);
	particles[gid].velocity += g * particles[gid].mass;

	/*vec2 force_of_gravity1 = calculate_gravity(gid, 0.0001, vec2(10.0, 360.0));
	vec2 force_of_gravity2 = calculate_gravity(gid, 0.0001, vec2(1270.0, 360.0));

	particles[gid].velocity += force_of_gravity1 * particles[gid].mass;
	particles[gid].velocity += force_of_gravity2 * particles[gid].mass;*/

	particles[gid].position += particles[gid].velocity;	
}

void main() {
	uint gid = gl_GlobalInvocationID.x;
	apply_forces(gid);
	//check_boundaries(gid);
}
