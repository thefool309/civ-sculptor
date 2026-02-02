#pragma once
#include "Civilization.h"

class CivFactory {
private:
    static CivId currentCivId;

	static std::vector<std::string> ReadCivNamesFromTxt(std::string& _filepath);
public:

    static CivSeed GenerateCivSeed(std::string name, uint64_t _worldSeed);

	static Civilization CreateCivilization(CivSeed seed);

	static Civilization CreateCivilization(std::string name, uint64_t _worldSeed);

	static std::unordered_map<std::string, Civilization> GenCivsFromList(std::string _filepath, uint64_t _worldSeed, RandomEngine rng);

};


