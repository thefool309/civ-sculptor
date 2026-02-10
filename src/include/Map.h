#pragma once
/// @file Map.h
/// @brief world map grid - tile storage, neighbor lookup, and procedural generation

#include <vector>
#include <thread>
#include <mutex>
#include "Tile.h"
#include "RandomEngine.h"


/// @brief 2D grid of tiles representing the world map
///
/// handles tile storage, neighbor caching, and procedural biome generation.
/// map generation runs on a dedicated thread with mutex protection.
class Map {
	std::vector<std::vector<Tile>> tiles; ///< 2D grid of tiles [y][x]
	int rows = Const::MAP_HEIGHT;    ///< number of rows (y axis)
	int columns = Const::MAP_WIDTH;  ///< number of columns (x axis)
	std::thread mapThread;           ///< dedicated thread for map generation
	std::mutex mapMootex;            ///< mutex protecting tile data during generation
public:
	/// @brief construct a blank map with all tiles set to Water
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

	/// @brief construct a map from a pre-built tile grid
	/// @param _tiles 2D vector of tiles to use
	Map(std::vector<std::vector<Tile>> _tiles) : tiles(_tiles) {
		rows = tiles.size();
		columns = tiles[0].size();
	}

	/// @brief join the map generation thread if still running
	~Map() {
		if(mapThread.joinable())
			mapThread.join();
	}

	/// @brief retrieve a tile by its coordinates
	/// @param x horizontal coordinate
	/// @param y vertical coordinate
	/// @return copy of the tile at (x, y)
	Tile getTile(uint32_t x, uint32_t y);

	/// @brief get all 8-directional neighbors of a tile (cached after first call)
	/// @param tile the tile to fetch neighbors for
	/// @return reference to the tile's neighbor vector
	std::vector<Tile*>& getNeighbors(Tile& tile);

	/// @brief procedurally generate biomes using a seeded BFS spreading algorithm
	///
	/// runs on a separate thread. seeds one tile per biome type in a random
	/// quadrant, then spreads via BFS with distance-based falloff probability.
	/// @param rng random engine for seed placement and spread rolls
	void generateMapTiles(RandomEngine& rng);

	/// @brief write a text representation of the map to stdout
	void writeMapToCout();

	/// @brief write a text representation of the map to a file
	/// @param _filepath path to write the output file
	void visualizeMapInTextFile(const char* _filepath);
};
