#include "ResourceManager.hpp"

#include "spdlog/spdlog.h"

// DEBT! Dependency injection
#include "NlohmannJsonParser.hpp"

ResourceManager::ResourceManager() {}

ResourceManager& ResourceManager::getInstance()
{
  static ResourceManager instance;
  return instance;
}

bool ResourceManager::loadTexture(const std::string& id,
  const std::string& texturePath)
{
  if (textures.find(id) != textures.end())
  {
    spdlog::info("Texture '{}' already loaded", id);
    return true;
  }

  sf::Texture texture;
  if (!texture.loadFromFile(texturePath))
  {
    spdlog::error("Failed to load texture: {}", texturePath);
    return false;
  }

  textures[id] = std::move(texture);
  spdlog::info("Loaded texture '{}' from {}", id, texturePath);

  return true;
}

bool ResourceManager::loadTextureData(const std::string& id,
  const std::string& textureDataPath)
{
  if (texturesDatas.find(id) != texturesDatas.end())
  {
    spdlog::info("Texture data '{}' already loaded", id);
    return true;
  }

  Animation::TextureData textureData =
    NlohmannJsonParser().parseTextureData(textureDataPath);

  if (textureData.frames.empty())
  {
    spdlog::error("Failed to load/parse texture data: {}", textureDataPath);
    return false;
  }

  texturesDatas[id] = std::move(textureData);
  spdlog::info("Loaded texture '{}' from {}", id, textureDataPath);

  return true;
}

bool ResourceManager::loadTextureAsset(const std::string& id, const std::string& texturePath,
  const std::string& textureDataPath)
{
  bool textureLoaded = loadTexture(id, texturePath);
  bool textureDataLoaded = loadTextureData(id, textureDataPath);

  return textureLoaded && textureDataLoaded;
}

bool ResourceManager::loadTileSetAsset(const std::string& id, const std::string& tileSetAssetPath)
{
  if (tileSets.find(id) != tileSets.end())
  {
    spdlog::info("tileset {} already loaded", id);
    return true;
  }

  // DEBT! try catch!
  try
  {
    // DEBT! store tileSetDTO when needed.
    TileSetDTO tileSetDTO = NlohmannJsonParser::parseTileSet(tileSetAssetPath);

    auto texture = std::make_unique<sf::Texture>();

    if(!texture->loadFromFile(tileSetDTO.texturePath))
    {
      spdlog::error("error loading texture", tileSetDTO.texturePath);
      throw std::runtime_error("error loading texture.");
    };

    tileMapTextures[id] = std::move(texture);

    auto tileSet = std::make_unique<TileSet>();

    tileSet->texture = tileMapTextures[id].get();
    tileSet->tileSize = tileSetDTO.tileSize;

    tileSets[id] = std::move(tileSet);


    spdlog::info("Loaded texture '{}' from {}", id, tileSetAssetPath);
    return true;
  }
  catch (const std::exception& e)
  {
    spdlog::error("error loading tile set asset {} on path {}.\n Error: {}", id, tileSetAssetPath, e.what());
    return false;
  }
}

const sf::Texture& ResourceManager::getTexture(
  const std::string& textureId) const
{
  auto it = textures.find(textureId);

  if (it != textures.end())
  {
    return it->second;
  }

  spdlog::warn("Texture {} not found. Returning default texture", textureId);
  return defaultTexture;
}

const Animation::TextureData& ResourceManager::getTextureData(
  const std::string& textureDataId) const
{
  auto it = texturesDatas.find(textureDataId);

  if (it != texturesDatas.end())
  {
    return it->second;
  }

  spdlog::warn("Texture data {} not found. Returning default texture data",
    textureDataId);
  return defaultTextureData;
}

const TileSet* ResourceManager::getTileSet(const std::string& tileSetId) const
{
  auto it = tileSets.find(tileSetId);

  if (it == tileSets.end())
  {

    spdlog::warn("tile set {} not found. Make sure it was loaded. Returning empty tile set.");

    return nullptr;
  }

  return it->second.get();
}
