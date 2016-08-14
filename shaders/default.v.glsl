#version 450

layout(location = 0) in vec3 vp;

uniform mat4 model;
uniform mat4 proj;

void main() {
	gl_Position = proj * model * vec4(vp, 1.0);
};