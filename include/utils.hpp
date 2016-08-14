#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <sstream>

#include "..\include\vec2.hpp"

namespace utils {
	template <typename T> T elapsed_time();

	float gen_random(float min = 0.f, float max = 10.f);

	static const maths::vec2f resolution = {1280.f, 720.f};
}