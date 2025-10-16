#include "AnimationComponent.hpp"

#include "SFML/Graphics/Texture.hpp"
#include "spdlog/spdlog.h"

AnimationComponent::AnimationComponent()
    : resourceManager(ResourceManager::getInstance())
{
}

void AnimationComponent::update(float deltaTime)
{
  updateAnimationFrame(deltaTime);
}

/**
 * in the future this function could allow custom frame rate per animation.
 * currently is fixed to FRAME_RATE
 */
void AnimationComponent::updateAnimationFrame(float deltaTime)
{
  const Animation::TextureData &textureData =
      resourceManager.getTextureData(currentTextureId);

  if (textureData.frames.empty())
  {
    return;
  }

  timeSinceLastFrame += deltaTime;

  while (timeSinceLastFrame >= frameDuration)
  {
    timeSinceLastFrame -= frameDuration;
    currentFrame = (currentFrame + 1) % textureData.frames.size();
  }
}

/**
 * aka playAnimation()
 */
void AnimationComponent::setAnimation(const std::string textureId)
{
  if(currentTextureId == textureId) return;

  currentTextureId = textureId;
  currentFrame = 0;

  spdlog::info("animation {} set.", textureId);
}

const sf::Texture &AnimationComponent::getCurrentTexture()
{
  return resourceManager.getTexture(currentTextureId);
};

const sf::IntRect AnimationComponent::getCurrentFrameRect() const
{
  Animation::TextureData textureData =
      resourceManager.getTextureData(currentTextureId);

  if (textureData.frames.empty())
  {
    spdlog::warn("texture data {} has no frames. Returning default IntRect");
    return sf::IntRect();
  }

  const Animation::Frame &frame = textureData.frames.at(currentFrame).frame;

  return sf::IntRect({frame.x, frame.y}, {frame.w, frame.h});
}

std::string AnimationComponent::getCurrentTextureId() const
{
  return currentTextureId;
}
