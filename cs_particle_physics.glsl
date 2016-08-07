#version 450

//struct Particle {
//	vec3 position;
//	vec3 rotation;
//	vec3 scale;
//
//	vec2 velocity;
//	vec2 acceleration;
//
//	float mass;
//};

struct Particle {
	vec3 position;
	vec3 scale;

	vec2 velocity;

	float mass;
};

layout(std430, binding = 0) buffer Particles {
	Particle particles[];
};

layout(local_size_x = 256) in;

void main() {
	const float intensity = 0.1;
	const float attractor_mass = 1.0;
	const vec2 attractor_location = vec2(683.0, 384.0);
	
	uint gid = gl_GlobalInvocationID.x;

	float d = distance(attractor_location, particles[gid].position.xy);//((force.x * force.x) + (force.y * force.y));
	float m = (intensity * attractor_mass * particles[gid].mass) / (d);// should be distance squared, but distance alone gives nicer results
	
	vec2 force = (attractor_location - particles[gid].position.xy) * m;

	particles[gid].velocity += (force / particles[gid].mass);//particles[gid].acceleration;
	particles[gid].position += vec3(particles[gid].velocity, 0.0);	
}

//////////////////////////////////////////////////////////////
// Boundary Collisions
//////////////////////////////////////////////////////////////
/*vec3 offset = particles[gid].scale * 0.5;
if (particles[gid].position.x > 1366.0 - offset.x) {
particles[gid].position.x = 1366.0 - offset.x;
particles[gid].velocity.x *= -1.0;
}
else if (particles[gid].position.x < offset.x) {
particles[gid].position.x = offset.x;
particles[gid].velocity.x *= -1.0;
}

if (particles[gid].position.y > 768.0 - offset.y) {
particles[gid].position.y = 768.0 - offset.y;
particles[gid].velocity.y *= -1.0;
}
else if (particles[gid].position.y < offset.y) {
particles[gid].position.y = offset.y;
particles[gid].velocity.y *= -1.0;
}*/
//////////////////////////////////////////////////////////////