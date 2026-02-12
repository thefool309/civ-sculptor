#pragma once
/// @file World.h
/// @brief world container holding the map, time, and global rng

#include <cstdint>
#include <string>
#include <fstream>
#include <iostream>
#include "RandomEngine.h"
#include "SimTime.h"
#include "Map.h"

/// @brief seed data for world generation
///
/// contains the master rng seed and world name. all deterministic
/// generation in the simulation derives from this seed.
struct WorldSeed {
	uint64_t rng_seed;  ///< master seed for all world randomness
	std::string name;   ///< world name


public:
	/// @param _seed rng seed value
	/// @param _name world name (defaults to "Random")
	explicit WorldSeed(uint64_t _seed, std::string _name = "Random") : rng_seed(_seed), name(_name) {}
};

/// @brief the world state - owns the map, simulation clock, and global rng
///
/// everything in the simulation exists within a World. the world's seed
/// determines the entire state of generation, making runs reproducible.
class World {
	WorldSeed seed;

public:
	RandomEngine globalRandEng = RandomEngine(seed.rng_seed); ///< global random engine seeded from world seed
	SimTime time;  ///< simulation clock
	Map map;       ///< the world map

	/// @brief construct from raw seed value and name, generates map immediately
	/// @param _seed rng seed value
	/// @param _name world name
	World(uint64_t _seed, std::string _name) : seed(_seed, _name), globalRandEng(_seed) {
		map.generateMapTiles(globalRandEng);
	}

	/// @brief construct from a WorldSeed object (deferred map generation)
	/// @param _seed pre-built WorldSeed
	World(WorldSeed _seed) : seed(_seed) {}

	/// @return the world's rng seed
	uint64_t getSeed() const { return seed.rng_seed; }
	/// @return the world name
	std::string getName() const { return seed.name; }
	/// @brief set a new rng seed
	/// @param _seed new seed value
	void setSeed(uint64_t _seed) { seed.rng_seed = _seed; }
	/// @brief set a new world name
	/// @param _name new name
	void setName(std::string _name) { seed.name = _name; }

	/// @brief serialize the world seed to a binary file
	/// @param _filepath path to write the seed data
	void WriteWorldSeed(std::string _filepath);

	/// @brief deserialize a world seed from a binary file
	/// @param _filepath path to read the seed data from
	void ReadWorldSeed(std::string _filepath);
};
