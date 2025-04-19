#pragma once

#include "AnimationData.hpp"
#include <memory>
#include <string>

class JsonParser
{
public:
  virtual ~JsonParser() = default;
  virtual Animation::TextureData parseTextureData(const std::string &textureDataPath) = 0;
};
