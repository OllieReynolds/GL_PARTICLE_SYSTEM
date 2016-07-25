#pragma once

namespace maths {
	class vec4 {
	protected:
		float n[4];

	public:
		vec4() : n{0} {}
		vec4(const float d) : n{d, d, d, d} {}
		vec4(const float x, const float y, const float z, const float w) : n{x, y, z, w} {}

		vec4& operator  = (const vec4& v) { n[0] = v[0];  n[1] = v[1];  n[2] = v[2];  n[3] = v[3]; return *this; }

		vec4 operator += (const vec4& v) { n[0] += v[0]; n[1] += v[1]; n[2] += v[2]; n[3] += v[3]; return *this; }
		vec4 operator -= (const vec4& v) { n[0] -= v[0]; n[1] -= v[1]; n[2] -= v[2]; n[3] -= v[3]; return *this; }

		float& operator [] (int i) { return n[i]; }
		const float& operator [] (int i) const { return n[i]; }
	};
}