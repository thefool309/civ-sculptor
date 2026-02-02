#include "Map.h"
#include "Tile.h"
#include <iostream>
/// <summary>
/// Retrieve a Tile object with x and y coordinates
/// </summary>
/// <param name="x">the x coordinate passed by value</param>
/// <param name="y">the y coordinate passed by value</param>
/// <returns>Tile</returns>
Tile Map::getTile(uint32_t x, uint32_t y) {
    
    if(!(x > rows) || !(y > columns))
        return tiles[x][y];
}

/// <summary>
/// a function for retrieving the neighboring Tile objects by position. Works eight ways and retrieves diagonal tiles as well
/// this will be used for spread mechanics and Breadth First Search algorithms.
/// </summary>
/// <param name="tile">- The tile to fetch the neighbors for. Passed by reference</param>
/// <returns>std::vector of Tile*</returns>
std::vector<Tile*>& Map::getNeighbors(Tile& tile) {
    if (!tile.neighbors.empty()) {
        return tile.neighbors;
    }
    std::vector<Tile*> result;
    constexpr int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    constexpr int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    for (int i = 0; i < 8; i++) {
        int nx = tile.x + dx[i];
        int ny = tile.y + dy[i];

        if (nx >= 0 && nx < columns && ny >= 0 && ny < rows) {
            result.push_back(&tiles[ny][nx]);
        }
    }
    // store the neighbors in the tile cache
    tile.neighbors = result;

    return result;
}

/// <summary>
/// Populate the map's tiles with biome types using a randomized seeding and probabilistic spreading algorithm.
/// For each terrain type (except Water) a random seed tile is chosen, then biomes spread to neighboring 
/// Water tiles using a (Breadth-first Search) BFS-like queue with a 60% chance to convert each neighbor.
/// </summary>
/// <param name="rng">- Random engine used to generate uniform integers and floats.
/// It is used to pick seed coordinates within Const::MAP_HEIGHT and Const::MAP_WIDTH and 
/// to roll the 60% spread chance for neighbors. Passed by value.</param>
void Map::generateMapTiles(RandomEngine rng) {
    constexpr int numOfBiomes = static_cast<int>(TerrainType::COUNT_TT);
    std::pair<int, int> seedCoords[numOfBiomes];

    std::vector<Tile*> seeds;
    std::unordered_map<TerrainType, std::pair<int, int>> seedCoordsMap;
    std::queue<Tile*> qu;
    // generate seed coordinates for each biome except water lol
    for (int i = 0; i < numOfBiomes; i++) {
        if (static_cast<TerrainType>(i) == TerrainType::Water) {
            continue;
        }
        seedCoords[i] = std::pair<int, int>(rng.generate_uniform_int(0, Const::MAP_HEIGHT - 1), rng.generate_uniform_int(0, Const::MAP_WIDTH - 1));
        seedCoordsMap.insert(std::pair<TerrainType, std::pair<int, int>>(static_cast<TerrainType>(i), seedCoords[i]));
        tiles[seedCoords[i].first][seedCoords[i].second].biome = static_cast<TerrainType>(i);
        seeds.push_back(&tiles[seedCoords[i].first][seedCoords[i].second]);
    }
    
    // load seeds into queue
    for (auto& seed: seeds) {
        qu.push(seed);
    }
    float baseChance = 0.75f;
    float falloff = 0.02f;
    // loop the queue
    while (!qu.empty()) {
        Tile* tile = qu.front();
        getNeighbors(*tile);
        for (auto& neighbor : tile->neighbors) {

            

            int dx = abs(static_cast<int>(neighbor->x - seedCoordsMap[tile->biome].first));
            int dy = abs(static_cast<int>(neighbor->y - seedCoordsMap[tile->biome].second));

            int manhattanDist = dx + dy;
            float chance = 1.0f;
            if (manhattanDist > 2) {
                 chance = std::max(baseChance - (manhattanDist * falloff), 0.25f);
            }

            float randomRoll = rng.generate_uniform_float();
            // 60% chance of spreading biome to neighbor
            if ((neighbor->biome == TerrainType::Water || neighbor->biome != tile->biome) && randomRoll < chance && !neighbor->beenSet)  {
                neighbor->biome = tile->biome;
                neighbor->beenSet = true;
                qu.push(neighbor);
            }
        }
        qu.pop();
    }
}

/// <summary>
/// write a visual representation of the map to std::cout
/// </summary>
void Map::writeMapToCout() {
    std::cout << '\n';
    for (int i = 0; i < tiles.size(); i++) {
        for (auto& tile : tiles[i]) {
            std::cout << Const::TerrainTypeSymbols[static_cast<size_t>(tile.biome)];
        }
        std::cout << '\n';
    }
}
/// <summary>
/// write a visual representation of the map to a text file
/// </summary>
/// <param name="_filepath">- the path to write the map to</param>
void Map::visualizeMapInTextFile(const char* _filepath) {
    
}
