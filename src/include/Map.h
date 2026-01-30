#pragma once

#include <vector>
#include "Tile.h"
#include "RandomEngine.h"

class Map {
	std::vector<std::vector<Tile>> tiles;
	int rows = Const::MAP_HEIGHT; //y
	int columns = Const::MAP_WIDTH; //x
public:
	Map() {
		// generate blank map
		tiles.resize(Const::MAP_HEIGHT);
		for (int y = 0; y < Const::MAP_HEIGHT; y++) {
			tiles[y].resize(Const::MAP_WIDTH);
			for (int x = 0; x < Const::MAP_WIDTH; x++) {
				tiles[y][x].x = x;
				tiles[y][x].y = y;
				tiles[y][x].biome = TerrainType::Water; // default terrain type is Water
			}
		}
	}

	Map(std::vector<std::vector<Tile>> _tiles) : tiles(_tiles) {
		rows = tiles.size();
		columns = tiles[0].size();
	}

	Tile getTile(uint32_t x, uint32_t y);

	std::vector<Tile*>& getNeighbors(Tile& tile);

	void generateMapTiles(RandomEngine rng);
};