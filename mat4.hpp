#pragma once

#include <cmath>

#include "vec3.hpp"
#include "vec4.hpp"

namespace maths {
	class mat4 {
	protected:
		vec4 n[4];
		
	public:
		mat4() : n{{1, 0, 0, 0},{0, 1, 0, 0},{0, 0, 1, 0},{0, 0, 0, 1}} {}
		mat4(const vec4& v0, const vec4& v1, const vec4& v2, const vec4& v3) : n{v0, v1, v2, v3} {}

		mat4& operator  = (const mat4& v) { 
			n[0] = v[0]; 
			n[1] = v[1]; 
			n[2] = v[2]; 
			n[3] = v[3]; 
			return *this;
		}

		inline vec4& operator [] (int i) { return n[i]; }
		inline const vec4& operator [] (int i) const { return n[i]; }

		inline mat4& translate(const vec3&v) {
			n[3][0] = v[0];
			n[3][1] = v[1];
			n[3][2] = v[2];
			return *this;
		}

		inline mat4& scale(const vec3& v) {
			n[0][0] = v[0];
			n[1][1] = v[1];
			n[2][2] = v[2];
			return *this;
		}

		friend mat4 translate_matrix(const vec3& v);
		friend mat4 scale_matrix(const vec3& v);
		friend mat4 rotate_x(const float f);
		friend mat4 rotate_y(const float f);
		friend mat4 rotate_z(const float f);
		friend mat4 orthogonal_perspective(float w, float h, float nZ, float fZ);
		friend mat4 orthogonal_perspective(float l, float r, float t, float b, float nZ, float fZ);
	};
}