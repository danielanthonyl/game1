#include "NlohmannJsonParser.hpp"

#include <fstream>

#include "nlohmann/json.hpp"

Animation::TextureData NlohmannJsonParser::parseTextureData(
    const std::string& textureDataPath)
{
  std::ifstream rawTextureData(textureDataPath);

  if (!rawTextureData.is_open())
  {
    throw std::runtime_error("Failed to open file: " + textureDataPath);
  }

  try
  {
    Animation::TextureData parsedTextureData;
    return parsedTextureData = nlohmann::json::parse(rawTextureData)
                                   .get<Animation::TextureData>();
  }
  catch (const std::exception& e)
  {
    throw std::runtime_error("Failed to parse file [" + textureDataPath + "]:\n" + e.what());
  }
}

InputContext::Context NlohmannJsonParser::parseInputContext(
    const std::string& inputContextId)
{
  std::string inputContextPath = "./" + inputContextId + ".json";
  std::ifstream rawInputContext(inputContextPath);

  if (!rawInputContext.is_open())
  {
    throw std::runtime_error("Failed to open file: " + inputContextPath);
  }

  try
  {
    InputContext::Context parsedInputContext;
    return parsedInputContext = nlohmann::json::parse(rawInputContext)
                                    .get<InputContext::Context>();
  }
  catch (const std::exception& e)
  {
    throw std::runtime_error("Failed to parse file [" + inputContextPath + "]:\n" + e.what());
  }
}


TileSetDTO NlohmannJsonParser::parseTileSet(const std::string& tileSetAssetPath)
{
  std::ifstream rawTileSet(tileSetAssetPath);

  if(!rawTileSet.is_open())
  {
    throw std::runtime_error("Failed to open tile set: " + tileSetAssetPath);
  }

  try
  {
    return nlohmann::json::parse(rawTileSet).get<TileSetDTO>();

  }
  catch(const std::exception& e)
  {
    throw std::runtime_error("Failed to parse file [" + tileSetAssetPath + "]:\n" + e.what());
  }
}