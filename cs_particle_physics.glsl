#version 430

struct Particle {
	vec3 position;
	vec3 rotation;
	vec3 scale;

	vec2 velocity;
	vec2 acceleration;

	float mass;
};

layout(std430, binding = 0) buffer Particles {
	Particle particles[];
};

layout(local_size_x = 128) in;

void main() {
	uint gid = gl_GlobalInvocationID.x;

	const float intensity = 0.1;
	const vec2 attractor_location = vec2(683.0, 384.0);
	const float attractor_mass = 1.0;
	
	float d = distance(attractor_location, particles[gid].position.xy);//((force.x * force.x) + (force.y * force.y));
	float m = (intensity * attractor_mass * particles[gid].mass) / (d);// should be distance squared, but distance alone gives nicer results
	
	vec2 force = attractor_location - particles[gid].position.xy;
	force = force * m;

	particles[gid].acceleration += (force / particles[gid].mass);
	particles[gid].velocity += particles[gid].acceleration;
	particles[gid].position += vec3(particles[gid].velocity, 0.0);
	

	vec3 offset = particles[gid].scale * 0.5;
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
	}

	particles[gid].acceleration = vec2(0.0);


/*
	float d = distance(vec2(683.0, 384.0), particles[gid].position.xy);
	float m = particles[gid].mass / (d * d);
	vec2 force = normalize(vec2(683.0, 384.0) - particles[gid].position.xy) * m;

	particles[gid].acceleration += 10000000.0 * (force / particles[gid].mass);
*/
	//particles[gid].velocity += particles[gid].accleration;

	/*uint gid = gl_GlobalInvocationID.x;
	particles[gid].position.xyz = vec3(600.0, 300.0, 0.0);*/
}