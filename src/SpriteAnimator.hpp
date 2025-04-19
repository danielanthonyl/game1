#pragma once

#include "SFML/Graphics.hpp"
#include "AnimationData.hpp"
#include "spdlog/spdlog.h"

enum class State
{
  IDLE,
  RUNNING
};

static std::map<State, std::string> StateToString = {
    {State::IDLE, "IDLE"},
    {State::RUNNING, "RUNNING"}};

class SpriteAnimator
{
public:
  SpriteAnimator();

  void add(const sf::Texture &texture,
           const Animation::TextureData &data,
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
  std::string parseState(State animationState);
  sf::Texture defaultTexture;

  struct StandbyConfig {
    int cyclesBeforeStandby = 0;
    int standbyFrame = 0;
    std::function<void()> onEnterStandby = nullptr;
  };

  struct AnimationConfig
  {
    sf::Texture texture;
    Animation::TextureData data;

    //DEBT! later on all of these should go inside "data"
    // but still needs to update the json file standard
    StandbyConfig standby;
    float frameTime;
  };

  sf::Sprite sprite;
  std::map<State, AnimationConfig> animations;

  State currentState = State::IDLE;
  int currentFrame = 0;
  float elapsedTime = 0.0f;

  int animationCycleCount = 0;
  bool inStandbyMode = false;
};
