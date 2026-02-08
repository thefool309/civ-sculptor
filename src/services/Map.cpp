#include "Map.h"
#include "Tile.h"

Tile Map::getTile(uint32_t x, uint32_t y) {
    
    if(x < rows && y < columns)
        return tiles[x][y];
}

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

void Map::generateMapTiles(RandomEngine rng) {
    constexpr int numOfBiomes = static_cast<int>(TerrainType::COUNT_TT);
    std::pair<int, int> seedCoords[numOfBiomes];

    std::vector<Tile*> seeds;

    std::queue<Tile*> qu;

    for (int i = 0; i < numOfBiomes; i++) {
        if (static_cast<TerrainType>(i) == TerrainType::Water) {
            continue;
        }
        seedCoords[i] = std::pair<int, int>(rng.generate_uniform_int(0, Const::MAP_HEIGHT - 1), rng.generate_uniform_int(0, Const::MAP_WIDTH - 1));
        tiles[seedCoords[i].first][seedCoords[i].second].biome = static_cast<TerrainType>(i);
        seeds.push_back(&tiles[seedCoords[i].first][seedCoords[i].second]);
    }

    for (auto& seed: seeds) {
        qu.push(seed);
    }

    while (!qu.empty()) {
        Tile* tile = qu.front();
        getNeighbors(*tile);
        for (auto& neighbor : tile->neighbors) {
            float randomRoll = rng.generate_uniform_float();
            if (neighbor->biome == TerrainType::Water && randomRoll < 0.6f) {
                neighbor->biome = tile->biome;
                qu.push(neighbor);
            }
        }
        qu.pop();
    }

}
