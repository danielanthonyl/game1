#include "animations.hpp"

void animate(const sf::Texture& texture, const SpriteSheet& spriteSheet, sf::Sprite& sprite)
{
  sprite.setTexture(texture);

  // currentFrame = (currentFrame + 1) % alucardIdle.frames.size();
  // Frame frame = alucardIdle.frames[currentFrame].frame;
  // sprite.setTextureRect(sf::IntRect({frame.x, frame.y}, {frame.w, frame.h}));
}