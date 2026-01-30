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

CivSeed World::GenerateCivSeed(const std::string& name) {
	// FNV-1a non cryptographic hashing algorithm

	//uses the name and world

	uint64_t hash = Const::FNV_offset_basis; // the hash starts as the offset basis

	for (auto& c : name) {
		hash ^= static_cast<uint64_t>(c);
		hash *= Const::FNV_prime;
	}

	hash ^= seed.rng_seed; // xor the world seed into it one time to make it deterministic
	hash *= Const::FNV_prime;

	return CivSeed(hash, name); 
}
