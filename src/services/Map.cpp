#include "Map.h"
#include "RandomEngine.h"
#include "Tile.h"
#include <iostream>
/// <summary>
/// Retrieve a Tile object with x and y coordinates
/// </summary>
/// <param name="x">the x coordinate passed by value</param>
/// <param name="y">the y coordinate passed by value</param>
/// <returns>Tile</returns>
Tile Map::getTile(uint32_t x, uint32_t y) {

  if (x < rows && y < columns)
    return tiles[x][y];
}

/// <summary>
/// a function for retrieving the neighboring Tile objects by position. Works
/// eight ways and retrieves diagonal tiles as well this will be used for spread
/// mechanics and Breadth First Search algorithms.
/// </summary>
/// <param name="tile">- The tile to fetch the neighbors for. Passed by
/// reference</param> <returns>std::vector of Tile*</returns>
std::vector<Tile *> &Map::getNeighbors(Tile &tile) {
  if (!tile.neighbors.empty()) {
    return tile.neighbors;
  }
  std::vector<Tile *> result;
  constexpr int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
  constexpr int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

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
/// seeded growth algorithm for map generation
///
/// Populate the map's tiles with biome types using a randomized seeding and
/// probabilistic spreading algorithm. For each terrain type (except Water) a
/// random seed tile is chosen, then biomes spread to neighboring Water tiles
/// using a (Breadth-first Search) BFS-like queue with a 60% chance to convert
/// each neighbor.
/// </summary>
/// <param name="rng">- Random engine used to generate uniform integers and
/// floats. It is used to pick seed coordinates within Const::MAP_HEIGHT and
/// Const::MAP_WIDTH and to roll the 60% spread chance for neighbors. Passed by
/// value.</param>
void Map::generateMapTiles(RandomEngine &rng) {

  mapThread = std::thread([this, &rng]() {
    std::lock_guard<std::mutex> lock(mapMootex);
    constexpr int numOfBiomes = static_cast<int>(TerrainType::COUNT_TT);
    std::pair<int, int> seedCoords[numOfBiomes];

    // quadrant_ranges[4/* the quadrant */][4]
    // inner array indexes 0 = ymin 1 = ymax 2 = xmin 3 = xmax
    int quadrant_ranges[4][4] = {
        {1, static_cast<int>(Const::MAP_HEIGHT * 0.25f), 1,
         static_cast<int>(Const::MAP_WIDTH * 0.25f)},
        {static_cast<int>(Const::MAP_HEIGHT * 0.25f) + 1,
         static_cast<int>(Const::MAP_HEIGHT * 0.50f),
         static_cast<int>(Const::MAP_WIDTH * 0.25f) + 1,
         static_cast<int>(Const::MAP_WIDTH * 0.50f)},
        {static_cast<int>(Const::MAP_HEIGHT * 0.50f) + 1,
         static_cast<int>(Const::MAP_HEIGHT * 0.75f),
         static_cast<int>(Const::MAP_WIDTH * 0.50f) + 1,
         static_cast<int>(Const::MAP_WIDTH * 0.75f)},
        {static_cast<int>(Const::MAP_HEIGHT * 0.75f) + 1, Const::MAP_HEIGHT,
         static_cast<int>(Const::MAP_WIDTH * 0.75f) + 1, Const::MAP_WIDTH}};

    std::queue<Tile *> qu;
    // generate seed coordinates for each biome except water lol
    for (int i = 0; i < numOfBiomes; i++) { // iterate through TerrainType
      if (static_cast<TerrainType>(i) == TerrainType::Water) {
        continue;
      }

      // randomly generate seed coords
      int quadrant = i / 2;

      int min_y = quadrant_ranges[quadrant][0];
      int max_y = quadrant_ranges[quadrant][1];
      int min_x = quadrant_ranges[quadrant][2];
      int max_x = quadrant_ranges[quadrant][3];

      seedCoords[i] =
          std::pair<int, int>(rng.generate_uniform_int(min_y, max_y - 1),
                              rng.generate_uniform_int(min_x, max_x - 1));

      // change tile biome type at seedCoords to current terrain type

      auto &seed = this->tiles[seedCoords[i].first][seedCoords[i].second];
      seed.biome = static_cast<TerrainType>(i);
      // load tile into queue
      qu.push(&seed);
    }

    // base chance for lat chance calculation
    constexpr float baseChance = 0.75f;
    constexpr float falloff = 0.01f;
    // loop the queue
    while (!qu.empty()) {
      // grab the tile at the front of the line

      Tile *tile = qu.front();

      getNeighbors(*tile); // grab tile neighbors into cache

      int biome_idx = static_cast<int>(tile->biome);
      int seed_x = seedCoords[biome_idx].second;
      int seed_y = seedCoords[biome_idx].first;

      for (auto *neighbor : tile->neighbors) {

        if (neighbor->beenSet)
          continue;
        if (neighbor->biome != TerrainType::Water &&
            neighbor->biome == tile->biome)
          continue;

        // calculate coordinates of the difference of neighbor.x - seed.x, and
        // neighbor.y - seed.y
        int dx = abs(static_cast<int>(neighbor->x - seed_x));
        int dy = abs(static_cast<int>(neighbor->y - seed_y));

        int manhattanDist = dx + dy; // manhattan distance for simplicity
        // if the manhattanDist is greater than 2
        // chance equals baseChance - (manhattanDist * falloff) clamped with a
        // min of 23% chance
        float chance =
            (manhattanDist > 10)
                ? std::max(baseChance - (manhattanDist * falloff), 0.23f)
                : 1.0f; // by default chance is set to 100

        if (rng.generate_uniform_float() <
            chance /* if random roll is less than chance */) {
          // set neighbors biome to tiles biome
          neighbor->biome = tile->biome;
          neighbor->beenSet = true;
          qu.push(neighbor); // push neighbor into queue
        }
      }
      // pop value off queue. Don't forget to do this ;-;
      qu.pop();
    }
  });
}

/// <summary>
/// write a visual representation of the map to std::cout
/// </summary>
void Map::writeMapToCout() {
  // buffer entire output to avoid per-symbol cout overhead
  std::string buf;
  size_t row_count = tiles.size();
  size_t col_count = row_count > 0 ? tiles[0].size() : 0;
  buf.reserve(row_count * (col_count + 1) + 1);

  buf += '\n';
  for (int i = 0; i < tiles.size(); i++) {
    for (auto &tile : tiles[i]) {
      buf += Const::TerrainTypeSymbols[static_cast<size_t>(tile.biome)];
    }
    buf += '\n';
  }
  std::cout.write(buf.data(), static_cast<std::streamsize>(buf.size()));
}
/// <summary>
/// write a visual representation of the map to a text file
/// </summary>
/// <param name="_filepath">- the path to write the map to</param>
void Map::visualizeMapInTextFile(const char *_filepath) {}
