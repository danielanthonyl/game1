#include "SpriteAnimator.hpp"
#include <iostream>

SpriteAnimator::SpriteAnimator() : sprite(getDummyTexture())
{
  sprite.scale({5.0f, 5.0f});
}

void SpriteAnimator::add(const sf::Texture &texture,
                         const SpriteSheet &data,
                         const State animationState,
                         const int cycles,
                         const int standbyFrame,
                         const float frameTime,
                         std::function<void()> onEnterStandby)
{
  Animation animation;
  animation.texture = texture;
  animation.data = data;

  animation.frameTime = frameTime;

  animation.standby.cyclesBeforeStandby = cycles;
  animation.standby.standbyFrame = standbyFrame;
  animation.standby.onEnterStandby = onEnterStandby;

  animations[animationState] = animation;
}

sf::Texture &SpriteAnimator::getDummyTexture()
{
  static sf::Texture dummyTexture;
  static bool dummyTextureInitialized = false;

  if (!dummyTextureInitialized)
  {
    // Create a 1x1 transparent pixel image
    sf::Image dummyImage;
    dummyImage.resize({1, 1}, sf::Color::Transparent);

    // Load the image into the texture
    bool success = dummyTexture.loadFromImage(dummyImage);
    if (!success)
    {
      std::cerr << "Failed to create dummy texture" << std::endl;
    }
    dummyTextureInitialized = true;
  }

  return dummyTexture;
}

void SpriteAnimator::update(const float &deltaTime)
{
  if (inStandbyMode)
  {
    return;
  }

  Animation &currentAnimation = animations[currentState];
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

    Animation &animation = animations[currentState];
    currentFrame = standby.standbyFrame;
    Frame standbyFrame = animation.data.frames[currentFrame].frame;
    sprite.setTextureRect(sf::IntRect({standbyFrame.x, standbyFrame.y}, {standbyFrame.w, standbyFrame.h}));

    if (standby.onEnterStandby)
    {
      standby.onEnterStandby();
    }
  };
};

void SpriteAnimator::play(const State animationState)
{
  if (currentState != animationState || inStandbyMode)
  {
    currentState = animationState;
    currentFrame = 0;
    elapsedTime = 0.0f;
    inStandbyMode = false;
    animationCycleCount = 0;

    Animation &animation = animations[currentState];
    sprite.setTexture(animation.texture);

    updateFrame();
  }
}

void SpriteAnimator::updateFrame()
{
  Animation &currentAnimation = animations[currentState];
  Frame frame = currentAnimation.data.frames[currentFrame].frame;
  sprite.setTextureRect(sf::IntRect({frame.x, frame.y}, {frame.w, frame.h}));
}

State SpriteAnimator::getState() const
{
  return currentState;
}

sf::Sprite SpriteAnimator::getSprite() const
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
