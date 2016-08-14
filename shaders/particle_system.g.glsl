#version 450

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

uniform mat4 projection;

in float vertex_scale[];
in float vertex_speed[];

out vec2 geom_uv;
out float geom_speed;

void main() {
	const vec4 position = gl_in[0].gl_Position;
	const float speed = vertex_speed[0];
	const float scale = vertex_scale[0] * 0.2;

	geom_speed = speed;

	gl_Position = projection * (position + vec4(-scale, -scale, 0, 0));
	geom_uv = vec2(0, 0);
	EmitVertex();

	gl_Position = projection * (position + vec4(-scale, scale, 0, 0));
	geom_uv = vec2(0, 1);
	EmitVertex();

	gl_Position = projection * (position + vec4(scale, -scale, 0, 0));
	geom_uv = vec2(1, 0);
	EmitVertex();

	gl_Position = projection * (position + vec4(scale, scale, 0, 0));
	geom_uv = vec2(1, 1);
	EmitVertex();

	EndPrimitive();
}
