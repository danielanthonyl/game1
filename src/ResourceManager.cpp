#include "ResourceManager.hpp"

ResourceManager::ResourceManager(std::unique_ptr<JsonParser> parser)
  : defaultTexture(sf::Vector2u(1, 1)),
    defaultTextureData(Animation::TextureData()),
    jsonParser(std::move(parser))
{
}

bool ResourceManager::loadTexture(const std::string id, const std::string texturePath)
{
  if(textures.find(id) != textures.end())
  {
    spdlog::info("Texture '{}' already loaded", id);
    return true;
  }

  sf::Texture texture;
  if(!texture.loadFromFile(texturePath))
  {
    spdlog::error("Failed to load texture: {}", texturePath);
    return false;
  }

  textures[id] = std::move(texture);
  spdlog::info("Loaded texture '{}' from {}", id, texturePath);

  return true;
}

bool ResourceManager::loadTextureData(const std::string id, const std::string textureDataPath)
{
  if(texturesDatas.find(id) != texturesDatas.end())
  {
    spdlog::info("Texture data '{}' already loaded", id);
    return true;
  }

  Animation::TextureData textureData = jsonParser->parseTextureData(textureDataPath);

  if(textureData.frames.empty())
  {
    spdlog::error("Failed to load/parse texture data: {}", textureDataPath);
    return false;
  }

  texturesDatas[id] = std::move(textureData);
  spdlog::info("Loaded texture '{}' from {}", id, textureDataPath);

  return true;
}

bool ResourceManager::loadTextureAsset(std::string id, std::string texturePath, std::string textureDataPath)
{
  bool textureLoaded = loadTexture(id, texturePath);
  bool textureDataLoaded = loadTextureData(id, textureDataPath);

  return textureLoaded && textureDataLoaded;
}
