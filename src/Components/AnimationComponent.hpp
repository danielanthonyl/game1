/**
 * DEBT! animation component will be split into SpriteComponent for handling texture management, rendering etc.
 */


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

  void playAnimation(const std::string textureId);
  void setTexture(const std::string textureId);

  const sf::Texture& getCurrentTexture();
  const sf::IntRect getCurrentFrameRect() const;

  const std::string& getCurrentTextureId() const;
  const size_t& getCurrentFrameInt() const;

private:
  std::string currentTextureId;
  bool isPlaying;

  size_t currentFrame;

  const float FRAME_RATE = 20.0f;
  float timeSinceLastFrame = 0.0f;

  ResourceManager& resourceManager;

  const float frameDuration = 1.0f / FRAME_RATE;

  void updateAnimationFrame(float deltaTime);
};

