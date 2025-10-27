#pragma once

#include "AnimationData.hpp"
#include "DataObjects/Tileset.hpp"

#include "SFML/Graphics/Texture.hpp"

class ResourceManager
{
public:
  explicit ResourceManager();

  // !DEBT! should have a loadAsset<DataObject>(); that would build the classes from the json.
  bool loadTileSetAsset(
    const std::string& id,
    const std::string& tileSetAssetPath);

  bool loadTextureAsset(
    const std::string& id,
    const std::string& texturePath,
    const std::string& textureDataPath);

  static ResourceManager& getInstance();
  const sf::Texture& getTexture(const std::string& textureId) const;
  const Animation::TextureData& getTextureData(const std::string& textureDataId) const;
  const TileSet* getTileSet(const std::string& tileSetId) const;

private:
  /* DEBT! should have a data object for each */
  std::map<const std::string, sf::Texture> textures;
  // DEBT! the textures should be a unique_ptr. needs refactor on other references.
  std::map<const std::string, std::unique_ptr<sf::Texture>> tileMapTextures;
  std::map<const std::string, Animation::TextureData> texturesDatas;
  std::map<const std::string, std::unique_ptr<TileSet>> tileSets;

  /* error handling */
  Animation::TextureData defaultTextureData;
  sf::Texture defaultTexture;

  bool loadTextureData(const std::string& id, const std::string& textureDataPath);
  bool loadTexture(const std::string& id, const std::string& texturePath);
};