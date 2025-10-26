#include "Player.hpp"

#include "Components/AnimationComponent.hpp"
#include "Components/InputContextComponent.hpp"
#include "GameConfig.hpp"
#include "InputContext.hpp"
#include "ResourceManager.hpp"
#include "SFMLKeyMap.hpp"
#include "spdlog/spdlog.h"

Player::Player() : Entity()
{
  name = "Player";
  initialScale = { 5.0f, 5.0f };
  friction = 0.1f;

  getInputContextComponent().bindContext("player-barefoot-icc");
  getAnimationComponent().setTexture(GameConfig::ResourceIds::PLAYER_IDLE);
  getAnimationComponent().playAnimation(GameConfig::ResourceIds::PLAYER_IDLE);
}


void Player::initialize()
{
  Entity::initialize();

  /** DEBT! player should be bottom center.
   * Need to check why collision isn't working when in bottom center
   */
  setPivotPoint(PivotPoints::CenterCenter);
  createBox();

  // setPosition({ 1.0f, 2.0f });
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

void Player::update(float deltaTime) {
  Entity::update(deltaTime);
}

void Player::moveForward(InputContext::TriggerEvent event)
{
  spdlog::info("handling forward movement");
  AnimationComponent& animationComponent = getAnimationComponent();

  // movement
  if (event == InputContext::TriggerEvent::Held)
  {
    addMovementInput(sf::Vector2f(1.0f, 0.0f));
  }

  // animations
  if (event == InputContext::TriggerEvent::Pressed)
  {
    animationComponent.playAnimation(GameConfig::ResourceIds::PLAYER_RUNNING);
  }

  if (event == InputContext::TriggerEvent::Released)
  {
    animationComponent.playAnimation(GameConfig::ResourceIds::PLAYER_IDLE);
  }
}

