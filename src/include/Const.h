#pragma once
#include <cstdint>
class Const {
public:
	static constexpr uint64_t FNV_offset_basis = 14695981039346656037;
	static constexpr uint64_t FNV_prime = 1099511628211;
};