#pragma once

#include "nlohmann/json.hpp"

// namespace json = nlohmann::json;

namespace Animation
{
  struct Frame { int x, y, w, h; };
  struct FrameData { Frame frame; std::string filename; int duration; };
  struct TextureData { std::vector<FrameData> frames; };

  NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Frame, x, y, w, h);
  NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(FrameData, frame, filename, duration);
  NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TextureData, frames);
};