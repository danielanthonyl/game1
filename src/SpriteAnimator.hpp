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
  SpriteAnimator();

  void add(const sf::Texture &texture,
           const SpriteSheet &data,
           const State animationState,
           const int cycles = 0,
           const int standbyFrame = 0,
           float frameTime = 0.1f,
           std::function<void()> onEnterStandby = nullptr);

  void update(const float &deltaTime);
  void play(const State animationState);

  const State getState() const;
  const sf::Sprite getSprite() const;

  bool isInStandby() const;
  void exitStandby();

private:
  void updateFrame();
  void updateStandbyState();
  sf::Texture defaultTexture;

  struct StandbyConfig {
    int cyclesBeforeStandby = 0;
    int standbyFrame = 0;
    std::function<void()> onEnterStandby = nullptr;
  };

  struct Animation
  {
    sf::Texture texture;
    SpriteSheet data;

    //DEBT! later on all of these should go inside "data"
    // but still needs to update the json file standard
    StandbyConfig standby;
    float frameTime;
  };

  sf::Sprite sprite;
  std::map<State, Animation> animations;

  State currentState;
  int currentFrame = 0;
  float elapsedTime = 0.0f;

  int animationCycleCount = 0;
  bool inStandbyMode = false;
};
