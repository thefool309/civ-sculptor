#pragma once
/// @file RandomEngine.h
/// @brief seeded random number generation and civilization seed structure

#include <random>
#include <optional>
#include <random>

/// @brief placeholder biome enum for CivSeed (unused currently)
enum Biome {
	COUNT_BI
};

/// @brief seed data for deterministic civilization generation
///
/// contains the rng seed derived from hashing the civ name with the world seed,
/// plus optional hints for initial state.
struct CivSeed {
	uint64_t rng_seed;  ///< deterministic seed for this civilization's rng
	std::string name;   ///< civilization name

	std::optional<int> tech_level;   ///< optional starting tech level
	std::optional<Biome> biome;      ///< optional preferred biome

	/// @param _seed rng seed value
	/// @param _name civilization name
	explicit CivSeed(uint64_t _seed, std::string _name) : rng_seed(_seed), name(_name) {}
};

/// @brief wrapper around mt19937 for deterministic random generation
///
/// all randomness in the simulation flows through this engine, seeded from
/// either the world seed or a civilization-specific seed for reproducibility.
class RandomEngine {
private:
  std::mt19937 rng;

public:
	/// @param seed initial seed for the mersenne twister
	explicit RandomEngine(uint64_t seed) : rng(seed) {}

	/// @brief generate a uniform random float in [min, max]
	/// @param min lower bound (default 0.0)
	/// @param max upper bound (default 1.0)
	/// @return random float value
	float generate_uniform_float(float min = 0.0, float max = 1.0);

	/// @brief generate a uniform random integer in [min, max]
	/// @param min lower bound
	/// @param max upper bound
	/// @return random integer value
	int generate_uniform_int(int min, int max);

	/// @brief get a copy of the internal mt19937 engine
	/// @return copy of the mersenne twister state
	std::mt19937 get_mt19937() const {
		return rng;
	}

	/// @brief generate a random enum value from 0 to count-1
	/// @tparam Enum the enum type to generate
	/// @param count number of valid enum values
	/// @return random enum value
	template<typename Enum>
	Enum generateRandomEnum(int count);
};
