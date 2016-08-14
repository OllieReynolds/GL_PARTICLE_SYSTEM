#include "..\include\vec2.hpp"

namespace maths {
	template<typename T>
	vec2<T> normalise(const vec2<T>& v) {
		if (v == vec2<T>(0, 0)) return v;
		return v / (magnitude(v));
	}

	template<typename T>
	T magnitude(const vec2<T>& v) {
		return sqrt(magnitude_squared(v));
	}

	template<typename T>
	T magnitude_squared(const vec2<T>& v) {
		return v.n[0] * v.n[0] + v.n[1] * v.n[1];
	}

	template<typename T>
	int operator == (const vec2<T>& a, const vec2<T>& b) {
		return (a[0] == b[0]) && (a[1] == b[1]);
	}

	template<typename T>
	int operator != (const vec2<T>& a, const vec2<T>& b) {
		return !(a == b);
	}

	template<typename T>
	vec2<T> operator + (const vec2<T>& v1, const vec2<T>& v2) {
		return vec2<T>(v1[0] + v2[0], v1[1] + v2[1]);
	}

	template<typename T>
	vec2<T> operator - (const vec2<T>& v1, const vec2<T>& v2) {
		return vec2<T>(v1[0] - v2[0], v1[1] - v2[1]);
	}

	template<typename T, typename T1>
	vec2<T1> operator * (const vec2<T>& v1, const T1 f) {
		return vec2<T1>(v1[0] * f, v1[1] * f);
	}

	template<typename T>
	vec2<T> operator / (const vec2<T>& v1, const T f) {
		return vec2<T>(v1[0] / f, v1[1] / f);
	}


	template vec2f normalise(const vec2f&);
	template float magnitude(const vec2f&);

	template vec2f operator - (const vec2f&, const vec2f&);
	template vec2f operator * (const vec2f&, const float);
	template vec2f operator / (const vec2f&, const float);
}