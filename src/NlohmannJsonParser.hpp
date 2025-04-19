#pragma once

#include "JsonParser.hpp"
#include "nlohmann/json.hpp"
#include <fstream>

class NlohmannJsonParser : public JsonParser
{
public:
  Animation::TextureData parseTextureData(const std::string& textureDataPath) override;
};
