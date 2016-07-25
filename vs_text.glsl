#version 450

layout(location = 0) in vec4 vp;

out vec2 tex_coord;

uniform mat4 proj;

void main() {
	gl_Position = proj * vec4(vp.xy, 0.0, 1.0);
	tex_coord = vec2(vp.zw);
};