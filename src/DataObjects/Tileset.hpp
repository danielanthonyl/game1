#pragma once

#include "SFML/Graphics.hpp"
#include "nlohmann/json.hpp"
#include "spdlog/spdlog.h"

// DTOS
// DEBT! maybe this is the "IntVector" engine vectors.
struct IntVector
{
  int width; // in pixels
  int height; // in pixels
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
  IntVector tileSize; // in pixels


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
  int width; // in tiles
  int height; // in tiles
};
