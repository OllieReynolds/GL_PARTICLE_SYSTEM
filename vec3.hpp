#pragma once

#include "vec2.hpp"

namespace maths {
	class vec3 {
	protected:
		float n[3];

	public:
		vec3() : n{0} {}
		vec3(const float d) : n{d, d, d} {}
		vec3(const float x, const float y, const float z) : n{x, y, z} {}
		vec3(const vec2f& v, const float d) : n{v[0], v[1], d} {}

		vec3& operator  = (const vec3& v) { n[0] = v[0]; n[1] = v[1]; n[2] = v[2]; return *this; }

		vec3& operator += (const vec3& v) { n[0] += v[0]; n[1] += v[1]; n[2] += v[2]; return *this; }
		vec3& operator -= (const vec3& v) { n[0] -= v[0]; n[1] -= v[1]; n[2] -= v[2]; return *this; }

		float& operator [] (int i) { return n[i]; }
		const float& operator [] (int i) const { return n[i]; }

		friend vec3 operator * (const vec3& v1, const float f);

		friend float magnitude(const vec3& v);
		friend float magnitude_squared(const vec3& v);
	};
}