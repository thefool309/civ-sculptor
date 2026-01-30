#pragma once
#include <cstdint>

class Const {
public:
	static constexpr uint64_t FNV_offset_basis = 14695981039346656037;
	static constexpr uint64_t FNV_prime = 1099511628211;

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

    
};