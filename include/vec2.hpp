#pragma once

#include <cmath>

namespace maths {
	template <typename T>
	class vec2 {
	public:
		vec2<T>() : n{{}} {}
		vec2<T>(const T f) : n{f, f} {}
		vec2<T>(const T x, T y) : n{x, y} {}

		vec2<T>& operator  = (const vec2<T>& v) { n[0] = v[0]; n[1] = v[1]; return *this; }

		vec2<T>& operator += (const vec2<T>& v) { n[0] += v[0]; n[1] += v[1]; return *this; }
		vec2<T>& operator -= (const vec2<T>& v) { n[0] -= v[0]; n[1] -= v[1]; return *this; }

		vec2<T>& operator *= (const T f) { n[0] *= f;    n[1] *= f;    return *this; }
		vec2<T>& operator /= (const T f) { n[0] /= f;    n[1] /= f;    return *this; }

		T& operator [] (int i) { return n[i]; }
		const T& operator [] (int i) const { return n[i]; }

		template <typename T>
		friend int operator == (const vec2<T>& a, const vec2<T>& b);

		template <typename T>
		friend int operator != (const vec2<T>& a, const vec2<T>& b);

		template <typename T>
		friend vec2<T> operator + (const vec2<T>& v1, const vec2<T>& v2);

		template <typename T>
		friend vec2<T> operator - (const vec2<T>& v1, const vec2<T>& v2);

		template <typename T, typename T1>
		friend vec2<T1> operator * (const vec2<T>& v1, const T1 f);

		template <typename T>
		friend vec2<T> operator / (const vec2<T>& v1, const T f);

		template <typename T>
		friend vec2<T> normalise(const vec2<T>& v);

		template <typename T>
		friend T magnitude(const vec2<T>& v);

		template <typename T>
		friend T magnitude_squared(const vec2<T>& v);


	protected:
		T n[2];
	};

	typedef vec2<double> vec2d;
	typedef vec2<float> vec2f;
	typedef vec2<int> vec2i;
}

