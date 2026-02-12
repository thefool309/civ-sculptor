#pragma once
/// @file Const.h
/// @brief compile-time constants and lookup tables for the simulation

#include <cstdint>

/// @brief central repository for simulation constants and lookup tables
class Const {
public:
	/// FNV-1a offset basis for deterministic hashing
	static constexpr uint64_t FNV_offset_basis = 14695981039346656037ULL;
	/// FNV-1a prime multiplier
	static constexpr uint64_t FNV_prime = 1099511628211ULL;

    /// default map width in tiles
    static constexpr int MAP_WIDTH = 100;
    /// default map height in tiles
    static constexpr int MAP_HEIGHT = 100;

    /// human-readable names for each ResourceType enum value
    static constexpr const char* ResourceTypeNames[] = {
    "Food",
    "Water",
    "Wood",
    "Stone",
    "Metal",
    "Gold",
    "Oil",
    "Nuclear Material"
    };

    /// human-readable names for each TerrainType enum value
    static constexpr const char* TerrainTypeNames[] = {
        "Plains",
        "Forest",
        "Hills",
        "Mountains",
        "Desert",
        "Tundra",
        "Water",
    };

    /// single-character symbols used for map text visualization
    static constexpr const char* TerrainTypeSymbols[] = {
        "P",
        "F",
        "H",
        "M",
        "D",
        "T",
        "W",
    };

};
