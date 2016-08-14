#include "..\include\vec3.hpp"

namespace maths {
	vec3 operator * (const vec3& v1, const float f) {
		return vec3(v1[0] * f, v1[1] * f, v1[2] * f);
	}

	float magnitude(const vec3& v) {
		return sqrt(magnitude_squared(v));
	}

	float magnitude_squared(const vec3& v) {
		return v.n[0] * v.n[0] + v.n[1] * v.n[1] + v.n[2] * v.n[2];
	}
}