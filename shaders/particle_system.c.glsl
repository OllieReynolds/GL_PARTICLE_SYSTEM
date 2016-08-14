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

layout(local_size_x = 128) in;

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

vec2 calculate_gravity(uint gid) {
	const float attractor_mass = 0.0001;
	const vec2 attractor_location = vec2(640.0, 360.0);

	float d = distance(attractor_location, particles[gid].position);//((force.x * force.x) + (force.y * force.y));
	float m = (attractor_mass * particles[gid].mass) / (d);// should be distance squared, but distance alone gives nicer results

	return (attractor_location - particles[gid].position) * m;
}

void apply_forces(uint gid) {
	vec2 force_of_gravity = calculate_gravity(gid);

	particles[gid].velocity += force_of_gravity * particles[gid].mass;//particles[gid].acceleration;
	particles[gid].position += particles[gid].velocity;	
}

void main() {
	uint gid = gl_GlobalInvocationID.x;

	apply_forces(gid);
	//check_boundaries(gid);
}
