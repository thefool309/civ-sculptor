#include "../include/CivFactory.h"
#include "Const.h"
#include <fstream>
#include <string>
#include<sstream>
#include<algorithm>

// must define static members outside the class

inline CivId CivFactory::currentCivId = 0;
/// <summary>
/// a private helper function for reading in civ names from a txt file 
/// </summary>
/// <param name="_filepath">- the path to the file to read from</param>
/// <returns>a vector of strings</returns>
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
/// <summary>
/// Generate a CivSeed from a civ name and the world rngSeed
/// </summary>
/// <param name="name">- name of the civ</param>
/// <param name="_worldSeed">- an unsigned 64 bit int that is the seed for all random generation in the world</param>
/// <returns>CivSeed object</returns>
CivSeed CivFactory::GenerateCivSeed(std::string name, uint64_t _worldSeed) {
	// FNV-1a non cryptographic hashing algorithm

	//uses the name and world

	uint64_t hash = Const::FNV_offset_basis; // the hash starts as the offset basis

	for (auto& c : name) {
		hash ^= static_cast<uint64_t>(c);
		hash *= Const::FNV_prime;
	}

	hash ^= _worldSeed; // xor the world seed into it one time to make it deterministic
	hash *= Const::FNV_prime;

	return CivSeed(hash, name);
}
/// <summary>
/// Create a single civilization directly from a CivSeed.
/// I found in some cases it made more sense to generate the CivSeed then use this function 
/// instead of passing in the raw values. 
/// It also kept me from having to write a default constructor for Civilization 
/// </summary>
/// <param name="seed">- CivSeed object that contains a name and an rngSeed</param>
/// <returns>Civilization object</returns>
Civilization CivFactory::CreateCivilization(CivSeed seed) {
	return Civilization(++currentCivId, seed.name, seed);
}
/// <summary>
/// creates a single civilization from a name and an unsigned 64 bit int world rng seed
/// </summary>
/// <param name="name">- The civilization name</param>
/// <param name="_rngSeed">- An unsigned 64 bit in that is the rng seed for the world</param>
/// <returns>Civilization object</returns>
Civilization CivFactory::CreateCivilization(std::string name, uint64_t _rngSeed) {
	CivSeed seed = GenerateCivSeed(name, _rngSeed);
	return Civilization(++currentCivId, seed.name, seed);
}
/// <summary>
///	a function for Generating civs from a list in a txt file
/// </summary>
/// <param name="_filepath">- the filepath to the file to read from</param>
/// <param name="_rngSeed">- an unsigned 64 bit int that is the rng seed for the world</param>
/// <param name="rng">- the random engine specifically for use in shuffling the civNames</param>
/// <returns>an unordered map of (std::string, Civilization)</returns>
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


