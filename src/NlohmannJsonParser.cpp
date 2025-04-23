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
    throw std::runtime_error("Failed to parse file [" + textureDataPath +
                             "]:\n" + e.what());
  }
}

InputContext::Context NlohmannJsonParser::parseInputContext(
    const std::string& inputContextData)
{
  std::ifstream rawInputContext(inputContextData);

  if (!rawInputContext.is_open())
  {
    throw std::runtime_error("Failed to open file: " + inputContextData);
  }

  try
  {
    InputContext::Context parsedInputContext;
    return parsedInputContext = nlohmann::json::parse(rawInputContext)
                                    .get<InputContext::Context>();
  }
  catch (const std::exception& e)
  {
    throw std::runtime_error("Failed to parse file [" + inputContextData +
                             "]:\n" + e.what());
  }
}