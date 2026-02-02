#include "../include/World.h"
#include "../include/Const.h"

void World::WriteWorldSeed(std::string _filepath) {
	std::ofstream fout(_filepath.c_str(), std::ios::binary);
	if (!fout) {
		printf("file unable to write! fout failed!\n\n");
		return;
	}
	// write rng seed
	fout.write(reinterpret_cast<const char*>(&seed.rng_seed), sizeof(seed.rng_seed));
	uint64_t nameLen = seed.name.size();
	// write the length of the name
	fout.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
	// write the name
	fout.write(seed.name.data(), nameLen);
}

void World::ReadWorldSeed(std::string _filepath) {
	std::ifstream fin(_filepath.c_str(), std::ios::binary);

	if (!fin) { throw std::runtime_error("File unable to open!"); }
	fin.open(_filepath);
	if (!fin.is_open()) { throw std::runtime_error("File unable to open!"); }
	// read in seed
	uint64_t rng_seed;
	fin.read(reinterpret_cast<char*>(&rng_seed), sizeof(rng_seed));
	// read in name length
	uint64_t nameLen;
	fin.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
	// read in name
	std::string name(nameLen, '\0');
	fin.read(name.data(), nameLen);
	// assign values to world seed
	seed.name = name;
	seed.rng_seed = rng_seed;
}
