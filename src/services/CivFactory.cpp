/// @file CivFactory.cpp
/// @brief CivFactory implementations - seed generation, civ creation, batch loading

#include "../include/CivFactory.h"
#include "Const.h"
#include <fstream>
#include <string>
#include<sstream>
#include<algorithm>

// must define static members outside the class

inline CivId CivFactory::currentCivId = 0;

std::vector<std::string> CivFactory::ReadCivNamesFromTxt(std::string& _filepath) {
	std::ifstream fin(_filepath);
	std::vector<std::string> civNames;
	if (!fin.is_open()) {
		throw std::runtime_error("file failed to open! check filepath!"); // throw runtime_error if failed to open
	}

	std::string line;
	while (std::getline(fin, line)) {
		if (line.empty()) continue;
		civNames.push_back(line);
	}

	return civNames;
}

CivSeed CivFactory::GenerateCivSeed(std::string name, uint64_t _worldSeed) {
	// FNV-1a non cryptographic hashing algorithm
	// uses the name and world seed for deterministic per-world generation

	uint64_t hash = Const::FNV_offset_basis; // the hash starts as the offset basis

	for (auto& c : name) {
		hash ^= static_cast<uint64_t>(c);
		hash *= Const::FNV_prime;
	}

	hash ^= _worldSeed; // xor the world seed into it one time to make it deterministic
	hash *= Const::FNV_prime;

	return CivSeed(hash, name);
}

Civilization CivFactory::CreateCivilization(CivSeed seed) {
	return Civilization(++currentCivId, seed.name, seed);
}

Civilization CivFactory::CreateCivilization(std::string name, uint64_t _rngSeed) {
	CivSeed seed = GenerateCivSeed(name, _rngSeed);
	return Civilization(++currentCivId, seed.name, seed);
}

std::unordered_map<std::string, Civilization> CivFactory::GenCivsFromList(std::string _filepath, uint64_t _rngSeed, RandomEngine rng) {
	std::vector<std::string> civNames;
	try {
		civNames = CivFactory::ReadCivNamesFromTxt(_filepath);
	}
	catch (std::runtime_error e) {
		std::cout << "File read failed: " << e.what() << '\n';
		return std::unordered_map<std::string, Civilization>();
	}
	catch (...) {
		std::cout << "File read failed: Unknown Exception" << '\n';
		return std::unordered_map<std::string, Civilization>();
	}

	auto& engine = rng.get_mt19937();

	std::shuffle(civNames.begin(), civNames.end(), engine);

	std::unordered_map<std::string, Civilization> result;

	for (auto& name : civNames) {
		result.insert(std::pair<std::string, Civilization>(name, CivFactory::CreateCivilization(name, _rngSeed)));
	}

	return result;
}


