#include "Player.hpp"

#include "Components/AnimationComponent.hpp"
#include "Components/InputContextComponent.hpp"
#include "GameConfig.hpp"
#include "InputContext.hpp"
#include "ResourceManager.hpp"
#include "SFMLKeyMap.hpp"
#include "spdlog/spdlog.h"

Player::Player(const std::string& id) : Entity(id)
{
  getInputContextComponent().bindContext("player-barefoot-icc");

  getAnimationComponent().setAnimation(GameConfig::ResourceIds::PLAYER_IDLE);
}

void Player::setupPlayerComponent()
{
  InputContextComponent& inputContextComponent = getInputContextComponent();

  const InputContext::Action* action =
      inputContextComponent.getAction("forward");

  if (!action)
  {
    spdlog::error("error getting action 'forward'");
    return;
  }

  inputContextComponent.bindAction(*action, &Player::moveForward, this);
}

void Player::update(float deltaTime) { Entity::update(deltaTime); }

void Player::moveForward(InputContext::TriggerEvent event)
{
  spdlog::info("handling forward movement");
  AnimationComponent& animationComponent = getAnimationComponent();

  // movement
  if(event == InputContext::TriggerEvent::Held)
  {
    setPosition(sf::Vector2f(4.0f, 0.0f));
  }

  // animations
  if (event == InputContext::TriggerEvent::Pressed)
  {
    animationComponent.setAnimation(GameConfig::ResourceIds::PLAYER_RUNNING);
  }

  if(event == InputContext::TriggerEvent::Released)
  {
    animationComponent.setAnimation(GameConfig::ResourceIds::PLAYER_IDLE);
  }
}
