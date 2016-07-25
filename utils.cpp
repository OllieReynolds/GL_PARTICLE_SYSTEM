#include "utils.hpp"

namespace utils {
	static const float M_PI = 3.1415926535897932384626433832795f;

	template <typename T>
	T elapsed_time() {
		using namespace std::chrono;
		static time_point<steady_clock> start = steady_clock::now();
		return duration_cast<duration<T>>(steady_clock::now() - start).count();
	}

	template <typename T>
	T gen_random(T min, T max) {
		static std::random_device rd;
		static std::mt19937 mt(rd());
		std::uniform_real_distribution<T> dist(min, max);
		return dist(mt);
	}
	
	template <>
	int gen_random(int min, int max) {
		static std::random_device rd;
		static std::mt19937 mt(rd());
		std::uniform_int_distribution<int> dist(min, max);
		return dist(mt);
	}

	template <typename T>
	void load_file(const char* fileName, T* data) {
		std::ifstream f;
		f.open(fileName, std::ifstream::in);
		if (!f.good())
			std::cout << "Error loading: " + std::string(fileName) << std::endl;

		std::string line;
		int index = 0;
		while (f.good() && std::getline(f, line)) {
			std::stringstream ss(line);		
			while (ss.good())
				ss >> data[index++];
		}
	}

	std::vector<float> cache_sin(const int frequency) {
		std::vector<float> vals;
		for (float phase = 0; phase < 2.f * M_PI; phase += (2.f * M_PI / frequency))
			vals.push_back(sin(phase));
		return vals;
	}

	std::vector<float> cache_cos(const int frequency) {
		std::vector<float> vals;
		for (float phase = 0; phase < 2.f * M_PI; phase += (2.f * M_PI / frequency))
			vals.push_back(cos(phase));
		return vals;
	}

	template float elapsed_time();
	template float gen_random(float, float);
	template void load_file(const char*, int*);
	template void load_file(const char*, float*);
	template void load_file(const char*, char*);
	template void load_file(const char*, std::string*);
}