#pragma once

#include <string>
#include <unordered_map>
#include "RandomEngine.h"
#include "Resources.h"
#pragma once
#include <iostream>
#include "Culture.h"
#include "Utils.h"



class Civilization {
	std::string civID;
	std::string name = "Testonia";
	bool hadTurnThisTick = false;
	long population = 2;
	std::unordered_map<ResourceType, Resources> resource_map;
	long research_points = 0;
	CulturalSummary cultural_summ;
	std::unordered_map<int, CulturalTrait> trait_map;
	RandomEngine rng;
	CivSeed seed;

public:
	Civilization(const std::string& _civID, const std::string& _name, CivSeed _seed) : civID(_civID), name(_name), seed(_seed), rng(_seed.rng_seed) {
		population = rng.generate_uniform_int(1000, 100000);
		resource_map.insert(std::pair<ResourceType, Resources>(ResourceType::Gold, Resources(ResourceType::Gold, rng.generate_uniform_int(0, 250))));
		std::cout << "The amount of " << Utils::ConvertResourceTypeToStringLiteral(ResourceType::Gold) << " generated for " << name << " is " << resource_map.at(ResourceType::Gold).amount << '\n';
		resource_map.insert(std::pair<ResourceType, Resources>(ResourceType::Stone, Resources(ResourceType::Stone, rng.generate_uniform_int(50, 500))));
		std::cout << "The amount of " << Utils::ConvertResourceTypeToStringLiteral(ResourceType::Stone) << " generated for " << name << " is " << resource_map.at(ResourceType::Stone).amount << '\n';
		resource_map.insert(std::pair<ResourceType, Resources>(ResourceType::Water, Resources(ResourceType::Water, rng.generate_uniform_int(100, 1000))));
		std::cout << "The amount of " << Utils::ConvertResourceTypeToStringLiteral(ResourceType::Water) << " generated for " << name << " is " << resource_map.at(ResourceType::Water).amount << '\n';
		resource_map.insert(std::pair<ResourceType, Resources>(ResourceType::Wood, Resources(ResourceType::Wood, rng.generate_uniform_int(100, 1000))));
		std::cout << "The amount of " << Utils::ConvertResourceTypeToStringLiteral(ResourceType::Wood) << " generated for " << name << " is " << resource_map.at(ResourceType::Wood).amount << '\n';
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

	void MakeTurn();

	void add_resource(ResourceType type, unsigned int amount);

};