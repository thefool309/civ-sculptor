#pragma once

#include <vector>
#include "Tile.h"

class Map {
	std::vector<std::vector<Tile>> tiles;
	int rows = tiles.size();
	int columns = tiles[0].size();

	Map(std::vector<std::vector<Tile>> _tiles) : tiles(_tiles) {
		rows = tiles.size();
		columns = tiles[0].size();
	}
public:
	Tile getTile(uint32_t x, uint32_t y);

	std::vector<Tile*> getNeighbors(Tile& tile);
};