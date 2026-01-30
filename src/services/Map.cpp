#include "Map.h"
enum class TerrainType: uint8_t {
    Plains,
    Forest,
    Hills,
    Mountains,
    Desert,
    Tundra,
    Water,

    COUNT_TT
};

Tile Map::getTile(uint32_t x, uint32_t y) {
    
    if((x > rows) || (y > columns))
        return tiles[x][y];
}

std::vector<Tile*> Map::getNeighbors(Tile& tile) {
    if (!tile.neighbors.empty()) {
        return tile.neighbors;
    }
    std::vector<Tile*> result;
    int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    for (int i = 0; i < 8; i++) {
        int nx = tile.x + dx[i];
        int ny = tile.y + dy[i];

        if (nx >= 0 && nx < rows && ny >= 0 && ny < columns) {
            result.push_back(&tiles[nx][ny]);
        }
    }
    // store the neighbors in the tile cache
    tile.neighbors = result;

    return result;
}
