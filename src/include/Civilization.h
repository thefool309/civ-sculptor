#pragma once

#include <string>
#include <unordered_map>
#include "RandomEngine.h"
#include "Resources.h"
#include "Culture.h"



class Civilization {
	std::string civID;
	std::string name = "Testonia";
	long population = 2;
	std::unordered_map<ResourceType, Resources> resource_map;
	long research_points = 0;
	CulturalSummary cultural_summ;
	std::unordered_map<int, CulturalTrait> trait_map;
	RandomEngine rng;
	CivSeed seed;

public:
	Civilization(const std::string& _civID, const std::string& _name, CivSeed _seed) : civID(_civID), name(_name), seed(_seed), rng(_seed.rng_seed) {
		resource_map.insert(std::pair<ResourceType, Resources>(ResourceType::gold, Resources(ResourceType::gold, 100)));
	}

	Civilization(const std::string& _civID, const std::string& _name, CivSeed _seed, const unsigned int& _pop, const std::unordered_map<ResourceType, Resources>& _resources)
		: civID(_civID), name(_name), seed(_seed), rng(_seed.rng_seed), population(_pop), resource_map(_resources) {
	}

	std::string get_name() {
		return name;
	}

	long get_population() {
		return population;
	}

	long get_research_points() {
		return research_points;
	}

	std::unordered_map<ResourceType, Resources> get_resource_map() {
		return resource_map;
	}

	void add_resource(ResourceType type, unsigned int amount);

};