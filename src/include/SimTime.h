#pragma once
#include <cstdint>

using SimTick = uint64_t;

struct SimTime {
	SimTick current_tick = 0;

	void advance(SimTick delta = 1ULL) {
		current_tick += delta;
	}
};