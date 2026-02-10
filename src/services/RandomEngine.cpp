/// @file RandomEngine.cpp
/// @brief RandomEngine method implementations

#include "../include/RandomEngine.h"

float RandomEngine::generate_uniform_float(float min, float max) {
	std::uniform_real_distribution<float> dist(min, max);
	return dist(rng);
}

int RandomEngine::generate_uniform_int(int min, int max) {
	std::uniform_int_distribution<int> dist(min, max);
	return dist(rng);
}

template<typename Enum>
Enum RandomEngine::generateRandomEnum(int count) {
	return static_cast<Enum>(generate_uniform_int(0, count - 1));
}
