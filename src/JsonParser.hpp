#pragma once

//DEBT! not being used. - waiting dependency injection refactor

#include "AnimationData.hpp"
#include <string>

class JsonParser
{
public:
  virtual ~JsonParser() = default;
  virtual Animation::TextureData parseTextureData(const std::string &textureDataPath) = 0;
};
