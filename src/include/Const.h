#pragma once
#include <cstdint>

class Const {
public:
	static constexpr uint64_t FNV_offset_basis = 14695981039346656037ULL;
	static constexpr uint64_t FNV_prime = 1099511628211ULL;

    static constexpr int MAP_WIDTH = 100;
    static constexpr int MAP_HEIGHT = 100;

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

    static constexpr const char* TerrainTypeNames[] = {
        "Plains",
        "Forest",
        "Hills",
        "Mountains",
        "Desert",
        "Tundra",
        "Water",
    };

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