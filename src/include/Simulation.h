#pragma once
/// @file Simulation.h
/// @brief top-level simulation controller - the "god object"

#include <unordered_map>
#include "World.h"
#include "CivFactory.h"
#include "Utils.h"
#include "Map.h"

/// @brief the top-level simulation controller
///
/// owns the World and all Civilizations. orchestrates map generation,
/// civilization creation, and the main simulation loop. this is the
/// glue that puts the puzzle together.
///
/// @see tests/test.h and tests/test.cpp for usage examples
class Simulation {
private:

public:
	World world; ///< the world state (map, time, rng)
	std::unordered_map<std::string, Civilization> civs; ///< all civilizations keyed by name


	/// @brief construct a simulation from a world seed
	/// @param _seed the WorldSeed that determines all generation
	Simulation(WorldSeed _seed) : world(_seed) {
		world.map.generateMapTiles(world.globalRandEng);
	}


	/// @brief generate 3 hardcoded test civilizations
	void Generate3Civs();

	/// @brief generate 5 hardcoded test civilizations
	void Generate5Civs();

	/// @brief generate 10 hardcoded test civilizations (fallout-themed)
	void Generate10Civs();

	/// @brief run the main simulation loop for a given number of ticks
	///
	/// each tick, every civilization takes their turn. the loop can be
	/// called in any increment and time persists between calls.
	/// @param _ticksToLoop number of ticks to execute
	/// @return the current tick after execution
	SimTick SimLoop(unsigned int _ticksToLoop);


};
