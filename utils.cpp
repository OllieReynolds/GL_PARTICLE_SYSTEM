#include "utils.hpp"

namespace utils {
	static const float M_PI = 3.1415926535897932384626433832795f;

	template <typename T> T elapsed_time() {
		using namespace std::chrono;
		static time_point<steady_clock> start = steady_clock::now();
		return duration_cast<duration<T>>(steady_clock::now() - start).count();
	}

	float gen_random(float min, float max) {
		static std::random_device rd;
		static std::mt19937 mt(rd());
		std::uniform_real_distribution<float> dist(min, max);
		return dist(mt);
	}

	template float elapsed_time();
}