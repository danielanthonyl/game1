#include "AnimationComponent.hpp"

AnimationComponent::AnimationComponent()
  : defaultTexture(sf::Vector2u(1, 1)), sprite(defaultTexture)
{};

void AnimationComponent::addAnimation(const std::string& textureId,
                                      const sf::Texture* texture,
                                      const Animation::TextureData* textureData,
                                      const int cycles,
                                      const int standbyFrame,
                                      const float frameTime,
                                      std::function<void()> onEnterStandby)
{
  TextureConfig textureConfig;

  textureConfig.textureId = textureId;
  textureConfig.texture = texture;
  textureConfig.textureData = textureData;
  textureConfig.frameTime = frameTime;
  textureConfig.standby.cyclesBeforeStandby = cycles;
  textureConfig.standby.standbyFrame = standbyFrame;
  textureConfig.standby.onEnterStandby = onEnterStandby;

  textures[textureId] = std::move(textureConfig);;
  spdlog::info("Added animation: {}", textureId);

  /* auto play the first added animation */
  if(textures.size() == 1)
  {
    play(textureId);
  }
}


void AnimationComponent::play(std::string textureId)
{
  auto it = textures.find(textureId);

  if(it == textures.end())
  {
    spdlog::error("animation '{}' not found", textureId);
    return;
  }

  spdlog::info("Animation switching: {} -> {}", currentTextureId, textureId);

  currentTextureId = textureId;
  currentFrame = 0;
  elapsedTime = 0.0f;
  inStandbyMode = false;
  animationCycleCount = 0;

  TextureConfig &textureConfig = textures[textureId];
  sprite.setTexture(*textureConfig.texture);
  updateFrame();
}

void AnimationComponent::updateFrame()
{
  auto it = textures.find(currentTextureId);

  if(it == textures.end())
  {
    spdlog::error("invalid animation '{}' for frame update", currentTextureId);
    return;
  }

  TextureConfig& currentAnimation = it->second;

  if(currentFrame < currentAnimation.textureData->frames.size())
  {
    Animation::Frame frame = currentAnimation.textureData->frames[currentFrame].frame;
    sprite.setTextureRect(sf::IntRect({frame.x, frame.y}, {frame.w, frame.h}));
  }
}

void AnimationComponent::update(float deltaTime)
{
  if(inStandbyMode || textures.empty() || currentTextureId.empty())
  {
    return;
  }

  auto it = textures.find(currentTextureId);

  if(it == textures.end())
  {
    spdlog::error("invalid animation '{}' for update", currentTextureId);;
    return;
  }

  TextureConfig& currentAnimation = it->second;
  elapsedTime += deltaTime;

  if(elapsedTime >= currentAnimation.frameTime)
  {
    elapsedTime = 0.0f;

    size_t lastFrame = currentAnimation.textureData->frames.size();
    bool wasLastFrame = currentFrame == lastFrame;

    currentFrame = (currentFrame + 1) % lastFrame;
    updateFrame();

    if(wasLastFrame)
    {
      animationCycleCount++;
      updateStandbyState();
    }
  }
}


void AnimationComponent::updateStandbyState()
{
  auto it = textures.find(currentTextureId);
  if(it == textures.end())
  {
    spdlog::error("invalid animation '{}' for standby update", currentTextureId);;
    return;
  }

  StandbyConfig& standby = it->second.standby;

  if(standby.cyclesBeforeStandby != 0 && animationCycleCount >= standby.cyclesBeforeStandby)
  {
    inStandbyMode = true;

    TextureConfig currentAnimation = it->second;
    currentFrame = standby.standbyFrame;

    if(currentFrame < currentAnimation.textureData->frames.size())
    {
      Animation::Frame standbyFrame = currentAnimation.textureData->frames[currentFrame].frame;
      sprite.setTextureRect(sf::IntRect({standbyFrame.x, standbyFrame.y}, {standbyFrame.w, standbyFrame.h}));
    }

    if(standby.onEnterStandby)
    {
      standby.onEnterStandby();
    }
  }
}