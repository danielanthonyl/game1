#pragma once

#include "SFML/Graphics.hpp"
#include "AnimationData.hpp"
#include "spdlog/spdlog.h"
#include "JsonParser.hpp"
#include <memory>

class ResourceManager
{
public:
  explicit ResourceManager(std::unique_ptr<JsonParser> parser);

  /**
   * @brief load texture assets from files
   * @param id unique identifier for the texture assets
   * @param texturePath file path to the texture file
   * @param textureDataPath file path to the texture data file (json)
   * @return bool True if loading was successful
   */
  bool loadTextureAsset(const std::string id,
                        const std::string texturePath,
                        const std::string textureDataPath);


  /**
   * @brief Load texture data from file
   * @param id unique identifier for the texture
   * @param textureDataPath file path to the texture file
   * @return bool True if loading was succesful
   */
  bool loadTextureData(const std::string id,
                       const std::string textureDataPath);

  /**
   * @brief Load texture data from file
   * @param id unique identifier for the texture
   * @param texturePath file path to the texture file
   * @return bool True if loading was succesful
   */
  bool loadTexture(const std::string id,
                   const std::string texturePath);

private:
  std::unique_ptr<JsonParser> jsonParser;
  std::map<std::string, sf::Texture> textures;
  std::map<std::string, Animation::TextureData> texturesDatas;

  sf::Texture defaultTexture;
  Animation::TextureData defaultTextureData;
};