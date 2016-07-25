#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <sstream>

namespace utils {
	template <typename T>
	T elapsed_time();

	template <typename T>
	T gen_random(T min, T max);

	template <>
	int gen_random(int min, int max);

	template <typename T>
	void load_file(const char* fileName, T* data);

	std::vector<float> cache_sin(const int frequency);
	std::vector<float> cache_cos(const int frequency);
}