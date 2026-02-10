#pragma once
/// @file SimTime.h
/// @brief simulation time tracking

#include <cstdint>

/// type alias for simulation tick counter
using SimTick = uint64_t;

/// @brief tracks the current tick of the simulation
///
/// time is measured in discrete ticks. each tick represents one full
/// round where every civilization takes their turn.
struct SimTime {
	SimTick current_tick = 0;

	/// @brief advance the clock by a given number of ticks
	/// @param delta number of ticks to advance (default 1)
	void advance(SimTick delta = 1ULL) {
		current_tick += delta;
	}
};
