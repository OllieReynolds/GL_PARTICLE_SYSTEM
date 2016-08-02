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

	const float intensity = 1000000.0;
	const vec2 attractor_location = vec2(683.0, 384.0);
	const float attractor_mass = 1000.0;

	vec2 force = attractor_location - particles[gid].position.xy;
	float d = ((force.x * force.x) + (force.y * force.y));
	float m = (intensity * attractor_mass * particles[gid].mass) / (d * d);
	force = normalize(force) * m;

	particles[gid].acceleration += (force / particles[gid].mass);
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