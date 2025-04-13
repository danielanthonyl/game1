#pragma once

#include "SFML/Graphics.hpp"
#include "spriteSheet.hpp"

enum class State
{
  IDLE,
  RUNNING
};

class SpriteAnimator
{
public:
  SpriteAnimator(sf::Sprite &spriteData);

  void add(const sf::Texture &texture, const SpriteSheet &data, const State animationState);
  void update(const float &deltaTime);
  void play(const State animationState);

  State getState() const;

private:
  void updateFrame();

  struct Animation
  {
    sf::Texture texture;
    SpriteSheet data;
  };

  sf::Sprite& sprite;
  std::map<State, Animation> animations;
  State currentState = State::IDLE;
  int currentFrame = 0;
  float elapsedTime = 0.0f;
};