#pragma once
#include "Civilization.h"
class CivFactory {
private:

public:
	static Civilization CreateCivilization(CivSeed seed) {
		return Civilization("C" + std::to_string(seed.rng_seed), seed.name, seed);
	}

};