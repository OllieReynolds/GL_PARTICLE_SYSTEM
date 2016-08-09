#version 450

// Share this with other shaders to avoid having to edit other shaders if the struct changes.
struct Particle {
	vec2 position;
	vec2 velocity;
	float scale;
	float mass;
};

layout(std430, binding = 0) buffer Particles {
	Particle particles[];
};

layout(std430, binding = 1) buffer ParticleMatrices {
	mat4 particle_matrices[];
};

layout(local_size_x = 128) in;

void check_boundaries(uint gid) {
	float offset = particles[gid].scale * 0.5;
	float t = 768.0 - offset;
	float r = 1366.0 - offset;

	if (particles[gid].position.x > r) {
		particles[gid].position.x = r;
		particles[gid].velocity.x *= -1.0;
	}
	else if (particles[gid].position.x < offset) {
		particles[gid].position.x = offset;
		particles[gid].velocity.x *= -1.0;
	}

	if (particles[gid].position.y > t) {
		particles[gid].position.y = t;
		particles[gid].velocity.y *= -1.0;
	}
	else if (particles[gid].position.y < offset) {
		particles[gid].position.y = offset;
		particles[gid].velocity.y *= -1.0;
	}
}

vec2 calculate_gravity(uint gid) {
	const float intensity = 0.05;
	const float attractor_mass = 1.0;
	const vec2 attractor_location = vec2(683.0, 384.0);

	float d = distance(attractor_location, particles[gid].position);//((force.x * force.x) + (force.y * force.y));
	float m = (intensity * attractor_mass * particles[gid].mass) / (d);// should be distance squared, but distance alone gives nicer results

	return (attractor_location - particles[gid].position) * m;
}

void apply_forces(uint gid) {
	vec2 force_of_gravity = calculate_gravity(gid);

	particles[gid].velocity += force_of_gravity / particles[gid].mass;//particles[gid].acceleration;
	particles[gid].position += particles[gid].velocity;	
}

void main() {
	uint gid = gl_GlobalInvocationID.x;

	apply_forces(gid);
	//check_boundaries(gid);

	particle_matrices[gid] = mat4(
		vec4(particles[gid].scale, 0.0, 0.0, 0.0),
		vec4(0.0, particles[gid].scale, 0.0, 0.0),
		vec4(0.0, 0.0, particles[gid].scale, 0.0),
		vec4(particles[gid].position.x, particles[gid].position.y, 0.0, 1.0)
	);
}