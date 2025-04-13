#include "SpriteAnimator.hpp"

SpriteAnimator::SpriteAnimator(sf::Sprite &spriteData) : sprite(spriteData)
{
};

void SpriteAnimator::add(const sf::Texture &texture, const SpriteSheet &data, const State animationState)
{
  Animation animation;
  animation.texture = texture;
  animation.data = data;

  animations[animationState] = animation;
};

void SpriteAnimator::update(const float &deltaTime)
{
  Animation &currentAnim = animations[currentState];

  elapsedTime += deltaTime;
  if (elapsedTime >= 0.1f)
  {
    elapsedTime = 0.0f;
    currentFrame = (currentFrame + 1) % currentAnim.data.frames.size();
    updateFrame();
  }
};

void SpriteAnimator::play(const State animationState)
{
  if (currentState != animationState)
  {
    currentState = animationState;
    currentFrame = 0;
    elapsedTime = 0.0f;

    Animation &animation = animations[currentState];

    sprite.setTexture(animation.texture);
    updateFrame();
  }
};

void SpriteAnimator::updateFrame()
{
  Animation &currentAnim = animations[currentState];
  Frame frame = currentAnim.data.frames[currentFrame].frame;
  sprite.setTextureRect(sf::IntRect({frame.x, frame.y}, {frame.w, frame.h}));
}

State SpriteAnimator::getState() const
{
  return currentState;
}
