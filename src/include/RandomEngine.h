#pragma once
#include <optional>
#include <random>

enum Biome { COUNT_BI };

struct CivSeed {
  uint64_t rng_seed;
  std::string name;

  std::optional<int> tech_level;
  std::optional<Biome> biome;

  explicit CivSeed(uint64_t _seed, std::string _name)
      : rng_seed(_seed), name(_name) {}
};

class RandomEngine {
private:
  std::mt19937 rng;

public:
  explicit RandomEngine(uint64_t seed) : rng(seed) {}

  float generate_uniform_float(float min = 0.0, float max = 1.0);

  int generate_uniform_int(int min, int max);

  std::mt19937 &get_mt19937() { return rng; }

  template <typename Enum> Enum generateRandomEnum(int count);
};