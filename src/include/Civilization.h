#pragma once
/// @file Civilization.h
/// @brief civilization entity - population, resources, culture, and turn logic

#include <iostream>
#include <string>
#include <unordered_map>
#include "RandomEngine.h"
#include "Resources.h"
#include "Culture.h"
#include "Utils.h"

/// type alias for civilization identifiers
using CivId = uint8_t;

/// @brief a single civilization in the simulation
///
/// each civilization has a population, resource stockpile, cultural traits,
/// and its own deterministic rng. civilizations take turns each tick,
/// making decisions influenced by their cultural summary.
class Civilization {
	CivId civID;                  ///< unique numeric identifier
	std::string name = "Testonia"; ///< civilization name
	bool hadTurnThisTick = false; ///< whether this civ has acted this tick
	long population = 2;          ///< current population count
	std::unordered_map<ResourceType, Resources> resource_map; ///< resource stockpile
	long research_points = 0;     ///< accumulated research
	CulturalSummary cultural_summ; ///< aggregate cultural statistics
	std::unordered_map<int, CulturalTrait> trait_map; ///< collection of active traits
	RandomEngine rng;             ///< civ-specific random engine
	CivSeed seed;                 ///< seed used to generate this civ

public:
	/// @brief construct a civilization with random initial resources
	/// @param _civID unique identifier
	/// @param _name civilization name
	/// @param _seed generation seed containing rng seed and name
	Civilization(CivId _civID, const std::string& _name, CivSeed _seed) : civID(_civID), name(_name), seed(_seed), rng(_seed.rng_seed) {
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

	/// @brief construct a civilization with explicit initial state
	/// @param _civID unique identifier
	/// @param _name civilization name
	/// @param _seed generation seed
	/// @param _pop initial population
	/// @param _resources initial resource stockpile
	Civilization(CivId _civID, const std::string& _name, CivSeed _seed, const unsigned int& _pop, const std::unordered_map<ResourceType, Resources>& _resources)
		: civID(_civID), name(_name), seed(_seed), rng(_seed.rng_seed), population(_pop), resource_map(_resources) {
	}

	/// @return the civilization's name
	std::string get_name() {
		return name;
	}

	/// @return current population count
	long get_population() {
		return population;
	}

	/// @return accumulated research points
	long get_research_points() {
		return research_points;
	}

	/// @return copy of the resource stockpile map
	std::unordered_map<ResourceType, Resources> get_resource_map() {
		return resource_map;
	}

	/// @brief execute this civilization's turn logic
	void MakeTurn();

	/// @brief add resources to the stockpile, creating the entry if it doesn't exist
	/// @param type which resource to add
	/// @param amount how much to add
	void add_resource(ResourceType type, unsigned int amount);

};
