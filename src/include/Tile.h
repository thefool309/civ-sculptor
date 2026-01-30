#pragma once

#include <cstdint>
#include <vector>
#include <unordered_map>
#include "Resources.h"
#include <queue>

enum class TerrainType : uint8_t {
    Plains,
    Forest,
    Hills,
    Mountains,
    Desert,
    Tundra,
    Water,

    COUNT_TT
};

struct Tile {
	uint32_t x;
	uint32_t y;

	std::vector<Tile*> neighbors;
	std::unordered_map<ResourceType, std::queue<ResourceDeposit>> deposits;
    TerrainType biome;
};