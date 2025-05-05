#include "ResourceManager.hpp"

#include "spdlog/spdlog.h"

// DEBT! Dependency injection
#include "NlohmannJsonParser.hpp"

ResourceManager::ResourceManager() {}

ResourceManager &ResourceManager::getInstance()
{
  static ResourceManager instance;
  return instance;
}

bool ResourceManager::loadTexture(const std::string id,
                                  const std::string texturePath)
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

bool ResourceManager::loadTextureData(const std::string id,
                                      const std::string textureDataPath)
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

bool ResourceManager::loadTextureAsset(std::string id, std::string texturePath,
                                       std::string textureDataPath)
{
  bool textureLoaded = loadTexture(id, texturePath);
  bool textureDataLoaded = loadTextureData(id, textureDataPath);

  return textureLoaded && textureDataLoaded;
}

/* Getters */

const sf::Texture &ResourceManager::getTexture(
    const std::string &textureId) const
{
  auto it = textures.find(textureId);

  if (it != textures.end())
  {
    return it->second;
  }

  spdlog::warn("Texture {} not found. Returning default texture", textureId);
  return defaultTexture;
}

const Animation::TextureData &ResourceManager::getTextureData(
    const std::string &textureDataId) const
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