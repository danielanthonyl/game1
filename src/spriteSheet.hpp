#pragma once

#include "nlohmann/json.hpp"

using json = nlohmann::json;

struct Frame
{
  int x, y, w, h;
};

struct FrameData
{
  Frame frame;
  std::string filename;
  int duration;
};

struct SpriteSheet
{
  std::vector<FrameData> frames;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Frame, x, y, w, h);
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(FrameData, frame, filename, duration);
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SpriteSheet, frames);
