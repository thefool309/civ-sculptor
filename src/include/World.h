#pragma once
#include <cstdint>
#include <string>
#include <fstream>
#include <iostream>
#include "RandomEngine.h"
#include "SimTime.h"
#include "Map.h"


struct WorldSeed {
	uint64_t rng_seed;
	std::string name;
	
	
public:
	explicit WorldSeed(uint64_t _seed, std::string _name = "Random") : rng_seed(_seed), name(_name) {}
};

class World {
	WorldSeed seed;
	
public:
	RandomEngine globalRandEng = RandomEngine(seed.rng_seed);
	SimTime time;
	Map map;

	World(uint64_t _seed, std::string _name) : seed(_seed, _name), globalRandEng(_seed) {
		map.generateMapTiles(globalRandEng);
	}

	World(WorldSeed _seed) : seed(_seed) {}

	uint64_t getSeed() const { return seed.rng_seed; }
	std::string getName() const { return seed.name; }
	void setSeed(uint64_t _seed) { seed.rng_seed = _seed; }
	void setName(std::string _name) { seed.name = _name; }

	void WriteWorldSeed(std::string _filepath);

	void ReadWorldSeed(std::string _filepath);
};