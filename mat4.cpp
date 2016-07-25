#include "mat4.hpp"

namespace maths {
	static const float M_PI = 3.1415926535897932384626433832795f;

	inline mat4 translate_matrix(const vec3& v) {
		return mat4(
			vec4(1.0, 0.0, 0.0, 0.0),
			vec4(0.0, 1.0, 0.0, 0.0),
			vec4(0.0, 0.0, 1.0, 0.0),
			vec4(v[0], v[1], v[2], 1.0)
		);
	}

	inline mat4 scale_matrix(const vec3& v) {
		return mat4(
			vec4(v[0], 0.0, 0.0, 0.0),
			vec4(0.0, v[1], 0.0, 0.0),
			vec4(0.0, 0.0, v[2], 0.0),
			vec4(0.0, 0.0, 0.0, 1.0)
		);
	}

	mat4 rotate_x(const float f) {
		//float rad = f * static_cast<float>(M_PI) / 180.f;
		float rad = f * float{M_PI} / 180.f;
		float c = cos(rad);
		float s = sin(rad);

		return mat4(
			vec4(1.0, 0.0, 0.0, 0.0),
			vec4(0.0, c, -s, 0.0),
			vec4(0.0, s, c, 0.0),
			vec4(0.0, 0.0, 0.0, 1.0)
		);
	}

	mat4 rotate_y(const float f) {
		float rad = f * static_cast<float>(M_PI) / 180.f;
		float c = cos(rad);
		float s = sin(rad);

		return mat4(
			vec4(c, 0.0, s, 0.0),
			vec4(0.0, 1.0, 0.0, 0.0),
			vec4(-s, 0.0, c, 0.0),
			vec4(0.0, 0.0, 0.0, 1.0)
		);
	}

	mat4 rotate_z(const float f) {
		float rad = f * static_cast<float>(M_PI) / 180.f;
		float c = cos(rad);
		float s = sin(rad);

		return mat4(
			vec4(c, -s, 0.0, 0.0),
			vec4(s, c, 0.0, 0.0),
			vec4(0.0, 0.0, 1.0, 0.0),
			vec4(0.0, 0.0, 0.0, 1.0)
		);
	}

	mat4 orthogonal_perspective(float w, float h, float nZ, float fZ) {
		float z = fZ - nZ;
		float i = -w / w;
		float j = -h / h;
		float k = -(fZ + nZ) / z;

		return mat4(
			vec4(2.f / w, 0.f, 0.f, 0.f),
			vec4(0.f, 2.f / h, 0.f, 0.f),
			vec4(0.f, 0.f, -2.f / z, 0.f),
			vec4(i, j, k, 1.f)
		);
	}

	mat4 orthogonal_perspective(float l, float r, float t, float b, float nZ, float fZ) {
		float w = r - l;
		float h = t - b;
		float z = fZ - nZ;
		float i = -w / w;
		float j = -h / h;
		float k = -(fZ + nZ) / z;

		return mat4(
			vec4(2.f / w, 0.f, 0.f, 0.f),
			vec4(0.f, 2.f / h, 0.f, 0.f),
			vec4(0.f, 0.f, -2.f / z, 0.f),
			vec4(i, j, k, 1.f)
		);
	}
}