/// @file Civilization.cpp
/// @brief Civilization turn logic and resource management

#include "../include/Civilization.h"

void Civilization::MakeTurn() {
	Utils::SetColor(93);
	std::cout << '\n' << name << " has made their turn\n";
	Utils::ResetColor();
}

void Civilization::add_resource(ResourceType type, unsigned int amount) {
	auto it = resource_map.find(type);

	if (it != resource_map.end()) {
		it->second.amount += amount;
	}
	else {
		resource_map.emplace(type, Resources(type, amount));
	}
}
