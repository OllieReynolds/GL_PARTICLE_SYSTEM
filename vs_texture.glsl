#version 450

layout(location = 0) in vec3 vp;
layout(location = 1) in vec2 uv;

out vec2 tex_coord;

uniform mat4 model;
uniform mat4 proj;

void main() {
	gl_Position = proj * model * vec4(vp, 1.0);
	tex_coord = vec2(uv.x, 1.0 - uv.y);
};