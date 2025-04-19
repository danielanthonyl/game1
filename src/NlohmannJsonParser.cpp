#include "NlohmannJsonParser.hpp"

Animation::TextureData NlohmannJsonParser::parseTextureData(const std::string& textureDataPath)
{
  std::ifstream rawTextureData(textureDataPath);

  if(!rawTextureData.is_open())
  {
    throw std::runtime_error("Failed to open file: " + textureDataPath);
  }

  try
  {
    Animation::TextureData parsedTextureData;
    return parsedTextureData = nlohmann::json::parse(rawTextureData).get<Animation::TextureData>();
  }
  catch(const std::exception& e)
  {
    throw std::runtime_error("Failed to parse file [" + textureDataPath + "]:\n" + e.what());
  }
}
