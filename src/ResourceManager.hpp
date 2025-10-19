#pragma once

#include "AnimationData.hpp"
#include "SFML/Graphics/Texture.hpp"

class ResourceManager
{
public:
  explicit ResourceManager();

  bool loadTextureAsset(
    const std::string& id,
    const std::string& texturePath,
    const std::string& textureDataPath);

  /* getters */
  static ResourceManager& getInstance();
  const sf::Texture& getTexture(const std::string& textureId) const;
  const Animation::TextureData& getTextureData(
    const std::string& textureDataId) const;

private:
  std::map<const std::string, sf::Texture> textures;
  std::map<const std::string, Animation::TextureData> texturesDatas;

  /* error handling */
  Animation::TextureData defaultTextureData;
  sf::Texture defaultTexture;

  bool loadTextureData(const std::string& id, const std::string& textureDataPath);
  bool loadTexture(const std::string& id, const std::string& texturePath);
};