#pragma once

#include "SFML/Graphics.hpp"
#include "nlohmann/json.hpp"
#include "spdlog/spdlog.h"

// DTOS
// DEBT! maybe this is the "IntVector" engine vectors.
struct IntVector
{
  int width;
  int height;
};

struct TileSetDTO
{
  std::string texturePath;
  IntVector tileSize; // in pixels
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(IntVector, width, height)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TileSetDTO, texturePath, tileSize)

// runtime data
struct TileSet
{
public:
  sf::Texture* texture;
  /**
   * Unit: Pixels
   */
  IntVector tileSize;
  /**
   * Unit: Tiles
   */
  IntVector tileSetSize;
};

struct TileInfo
{
  size_t tileIndex;
  const TileSet* tileSet;
};

// DEBT! this will behave as TileMap while no multi-layer is implemented.
struct TileLayer
{
  std::vector<std::unique_ptr<TileInfo>> tiles;
  /**
   * DOC! tiles.size() must equal width * height;
   * the width and height, defines the grid. Inconsistent values will break rendering logic.
   *
   * */
  int width; // in tiles
  int height; // in tiles
};
