#include "SpriteAnimator.hpp"
#include <iostream>

/**
 * - support atlas texture
 * - per frame callbacks
 * - add in house serialization
 *
 */

SpriteAnimator::SpriteAnimator()
    : defaultTexture(sf::Vector2u(2, 2)), sprite(defaultTexture)
{
  // DEBT! temporary
  sprite.scale({5.0f, 5.0f});
}

void SpriteAnimator::add(const sf::Texture &texture,
                         const Animation::TextureData &data,
                         const State animationState,
                         const int cycles,
                         const int standbyFrame,
                         const float frameTime,
                         std::function<void()> onEnterStandby)
{
  AnimationConfig animation;
  animation.texture = texture;
  animation.data = data;

  animation.frameTime = frameTime;

  animation.standby.cyclesBeforeStandby = cycles;
  animation.standby.standbyFrame = standbyFrame;
  animation.standby.onEnterStandby = onEnterStandby;

  animations[animationState] = animation;
}

void SpriteAnimator::update(const float &deltaTime)
{
  if (inStandbyMode)
  {
    return;
  }

  AnimationConfig &currentAnimation = animations[currentState];
  elapsedTime += deltaTime;

  if (elapsedTime >= currentAnimation.frameTime)
  {
    elapsedTime = 0.0f;

    int lastFrame = currentAnimation.data.frames.size() - 1;
    bool wasLastFrame = (currentFrame == lastFrame);

    currentFrame = (currentFrame + 1) % currentAnimation.data.frames.size();
    updateFrame();

    if (wasLastFrame)
    {
      animationCycleCount++;
      updateStandbyState();
    }
  }
}

void SpriteAnimator::updateStandbyState()
{
  StandbyConfig &standby = animations[currentState].standby;

  if (standby.cyclesBeforeStandby != 0 && animationCycleCount >= standby.cyclesBeforeStandby)
  {
    inStandbyMode = true;

    AnimationConfig &animation = animations[currentState];
    currentFrame = standby.standbyFrame;
    Animation::Frame standbyFrame = animation.data.frames[currentFrame].frame;
    sprite.setTextureRect(sf::IntRect({standbyFrame.x, standbyFrame.y}, {standbyFrame.w, standbyFrame.h}));

    if (standby.onEnterStandby)
    {
      standby.onEnterStandby();
    }
  };
};

void SpriteAnimator::play(const State animationState)
{
  spdlog::info("animation switching: {} -> {}", parseState(currentState), parseState(animationState));

    currentState = animationState;
    currentFrame = 0;
    elapsedTime = 0.0f;
    inStandbyMode = false;
    animationCycleCount = 0;

    AnimationConfig &animation = animations[currentState];
    sprite.setTexture(animation.texture);

    updateFrame();
}

void SpriteAnimator::updateFrame()
{
  AnimationConfig &currentAnimation = animations[currentState];
  Animation::Frame frame = currentAnimation.data.frames[currentFrame].frame;
  sprite.setTextureRect(sf::IntRect({frame.x, frame.y}, {frame.w, frame.h}));
}

const State SpriteAnimator::getState() const
{
  return currentState;
}

const sf::Sprite SpriteAnimator::getSprite() const
{
  return sprite;
}

bool SpriteAnimator::isInStandby() const
{
  return inStandbyMode;
}

void SpriteAnimator::exitStandby()
{
  if (inStandbyMode)
  {
    inStandbyMode = false;
    currentFrame = 0;
    elapsedTime = 0.0f;
    animationCycleCount = 0;
    updateFrame();
  };
}

std::string SpriteAnimator::parseState(State animationState)
{
  auto it = StateToString.find(animationState);
  return it != StateToString.end() ? it->second : "UNKNOWN";
}
