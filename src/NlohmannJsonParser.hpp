#pragma once

#include "InputContext.hpp"
#include "JsonParser.hpp"

class NlohmannJsonParser : public JsonParser
{
 public:
  Animation::TextureData parseTextureData(
      const std::string& textureDataPath) override;

  static InputContext::Context parseInputContext(
      const std::string& inputContextId);
};
