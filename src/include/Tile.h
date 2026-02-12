#pragma once
/// @file Tile.h
/// @brief tile structure and terrain types for the world map

#include <cstdint>
#include <vector>
#include <unordered_map>
#include "Resources.h"
#include <queue>

/// @brief terrain biome types that a tile can have
///
/// each tile on the map is assigned one of these types during generation.
/// Water is the default/unset state.
enum class TerrainType : uint8_t {
    Plains,
    Forest,
    Hills,
    Mountains,
    Desert,
    Tundra,
    Water,

    COUNT_TT ///< sentinel value, total number of terrain types
};

/// @brief a single cell on the world map
///
/// holds position, biome type, neighbor cache, and resource deposits.
/// neighbors are lazily populated on first access via Map::getNeighbors().
struct Tile {
	uint32_t x;  ///< horizontal position on the map
	uint32_t y;  ///< vertical position on the map
    bool beenSet = false; ///< whether biome has been assigned during generation

	std::vector<Tile*> neighbors; ///< cached adjacent tiles (populated lazily)
	std::unordered_map<ResourceType, std::queue<ResourceDeposit>> deposits; ///< extractable resource deposits
    TerrainType biome; ///< terrain type assigned to this tile
};
