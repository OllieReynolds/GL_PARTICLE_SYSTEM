#pragma once

#include "vec2.hpp"
#include "utils.hpp"

namespace utils {
	inline static const maths::vec2f resolution() {
		static maths::vec2f data = []()->maths::vec2f { 
			float tmp[2];
			utils::load_file("CONFIG.txt", tmp);
			return {tmp[0], tmp[1]}; 
		}();
		return data;
	}


	inline static const float* unit_triangle() {
		static float* data = []()->float* {
			float tmp[9];
			utils::load_file("unit_triangle.dat", tmp);
			return tmp;
		}();
		return data;
	}

	inline static const float* unit_square() {
		static float* data = []()->float* {
			float tmp[18];
			utils::load_file("unit_square.dat", tmp);
			return tmp;
		}();
		return data;
	}
}