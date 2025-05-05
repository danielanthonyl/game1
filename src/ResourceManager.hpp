#pragma once

#include "AnimationData.hpp"
#include "SFML/Graphics/Texture.hpp"

class ResourceManager
{
 public:
  explicit ResourceManager();

  /**
   * @brief load texture assets from files
   * @param id unique identifier for the texture assets
   * @param texturePath file path to the texture file
   * @param textureDataPath file path to the texture data file (json)
   * @return bool True if loading was successful
   */
  bool loadTextureAsset(const std::string id, const std::string texturePath,
                        const std::string textureDataPath);

  /**
   * @brief Load texture data from file
   * @param id unique identifier for the texture
   * @param textureDataPath file path to the texture file
   * @return bool True if loading was succesful
   */
  bool loadTextureData(const std::string id, const std::string textureDataPath);

  /**
   * @brief Load texture data from file
   * @param id unique identifier for the texture
   * @param texturePath file path to the texture file
   * @return bool True if loading was succesful
   */
  bool loadTexture(const std::string id, const std::string texturePath);

  /* getters */
  static ResourceManager& getInstance();
  const sf::Texture& getTexture(const std::string& textureId) const;
  const Animation::TextureData& getTextureData(
      const std::string& textureDataId) const;

 private:
  std::map<std::string, sf::Texture> textures;
  std::map<std::string, Animation::TextureData> texturesDatas;

  /* error handling */
  Animation::TextureData defaultTextureData;
  sf::Texture defaultTexture;
};