#pragma once

#include <functional>
#include <map>
#include <string>

#include "../AnimationData.hpp"
#include "../ResourceManager.hpp"

class AnimationComponent
{
 public:
  AnimationComponent();

  void update(float deltaTime);

  void setAnimation(const std::string textureId);

  const sf::Texture &getCurrentTexture();
  const sf::IntRect getCurrentFrameRect() const;

  std::string getCurrentTextureId() const;

 private:
  void updateAnimationFrame(float deltaTime);

  ResourceManager& resourceManager;
  std::string currentTextureId;
  size_t currentFrame;

  const float FRAME_RATE = 20.0f;
  float timeSinceLastFrame = 0.0f;
  const float frameDuration = 1.0f / FRAME_RATE;

};

