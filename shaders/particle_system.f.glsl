#version 450

in vec2 geom_uv;
in float geom_speed;

out vec4 frag_colour;

void main() {
	float d = distance(geom_uv, vec2(0.5, 0.5));
	float c = geom_speed * 0.3;
	
	vec4 colour = vec4(c, 0.0, 1.2 - c, 0.05);
	colour.a *= pow((1.0 - (2.0 * d)), 0.5);

	frag_colour = colour;
};