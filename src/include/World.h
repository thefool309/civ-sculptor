#pragma once
#include <cstdint>
#include <string>
#include <fstream>
#include <iostream>
#include "RandomEngine.h"


struct WorldSeed {
	uint64_t rng_seed;
	std::string name;
public:
	explicit WorldSeed(uint64_t _seed, std::string _name = "Random") : rng_seed(_seed), name(_name) {}
};

class World {
	WorldSeed seed;
public:
	World(uint64_t _seed, std::string _name) : seed(_seed, _name) {}

	uint64_t getSeed() const { return seed.rng_seed; }
	std::string getName() const { return seed.name; }
	void setSeed(uint64_t _seed) { seed.rng_seed = _seed; }
	void setName(std::string _name) { seed.name = _name; }

	void WriteWorldSeed(std::string _filepath);

	void ReadWorldSeed(std::string _filepath);

	CivSeed GenerateCivSeed(const std::string& name);
};