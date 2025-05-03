#include "Player.hpp"

#include "AnimationComponent.hpp"
#include "GameConfig.hpp"
#include "InputContext.hpp"
#include "InputContextComponent.hpp"
#include "ResourceManager.hpp"
#include "SFMLKeyMap.hpp"
#include "spdlog/spdlog.h"

Player::Player(const std::string& id) : Entity(id)
{
  initializeAnimations();
  getInputContextComponent().bindContext("player-barefoot-icc");
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

  inputContextComponent.bindAction(InputContext::ActionHandler{
      *action, std::bind(&Player::moveForward, this)});
}

void Player::update(float deltaTime)
{
  handleInput();
  Entity::update(deltaTime);
}

void Player::initializeAnimations()
{
  AnimationComponent& animationComponent = getAnimationComponent();
  auto& resourceManager = ResourceManager::getInstance();

  animationComponent.addAnimation(
      GameConfig::AnimationStates::IDLE,
      &resourceManager.getTexture(GameConfig::ResourceIds::PLAYER_IDLE),
      &resourceManager.getTextureData(GameConfig::ResourceIds::PLAYER_IDLE));

  animationComponent.addAnimation(
      GameConfig::AnimationStates::RUNNING,
      &resourceManager.getTexture(GameConfig::ResourceIds::PLAYER_RUNNING),
      &resourceManager.getTextureData(GameConfig::ResourceIds::PLAYER_RUNNING));
}

void Player::handleInput()
{
  AnimationComponent& animationComponent = getAnimationComponent();
  InputContextComponent& inputContextComponent = getInputContextComponent();
  const InputContext::Action* action =
      inputContextComponent.getAction("forward");

  if (!action)
  {
    spdlog::error("Action component not found.");
    return;
  }

  sf::Keyboard::Key forwardKey = SFMLKeyMap::toKey(action->key);

  bool wasMoving = isMoving;
  isMoving = false;

  if (sf::Keyboard::isKeyPressed(forwardKey))
  {
    isMoving = true;

    if (!wasMoving)
    {
      if (animationComponent.getCurrentAnimationId() !=
          GameConfig::AnimationStates::RUNNING)
      {
        animationComponent.play(GameConfig::AnimationStates::RUNNING);
      }
    }
  }
  else
  {
    if (wasMoving)
    {
      if (animationComponent.getCurrentAnimationId() !=
          GameConfig::AnimationStates::IDLE)
      {
        animationComponent.play(GameConfig::AnimationStates::IDLE);
      }
    }
  }
}

void Player::moveForward()
{
  spdlog::info("handling forward movement");

  AnimationComponent& animationComponent = getAnimationComponent();
  // animation component.move? this is wrong. entity should own sprite.
  animationComponent.getSprite().move(sf::Vector2f(3.0f, 0.0f));
}