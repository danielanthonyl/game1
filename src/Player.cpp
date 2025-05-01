#include "Player.hpp"

#include "GameConfig.hpp"
#include "InputContextComponent.hpp"
#include "ResourceManager.hpp"
#include "SFMLKeyMap.hpp"
#include "spdlog/spdlog.h"

Player::Player(const std::string& id) : Entity(id)
{
  initializeAnimations();
  getInputContextComponent().addContext("player-barefoot-icc");
}

void Player::update(float deltaTime)
{
  handleInput();
  Entity::update(deltaTime);
}

void Player::initializeAnimations()
{
  auto& animationComponent = addAnimationComponent();
  auto& resourceManager = ResourceManager::getInstance();

  animationComponent.addAnimation(
      GameConfig::AnimationStates::IDLE,
      &resourceManager.getTexture(GameConfig::ResourceIds::PLAYER_IDLE),
      &resourceManager.getTextureData(GameConfig::ResourceIds::PLAYER_IDLE));

  animationComponent.addAnimation(
      GameConfig::AnimationStates::RUNNING,
      &resourceManager.getTexture(GameConfig::ResourceIds::PLAYER_RUNNING),
      &resourceManager.getTextureData(GameConfig::ResourceIds::PLAYER_RUNNING));

  /* maybe we dont need this because the other function already has it */
  animationComponent.play(GameConfig::AnimationStates::IDLE);
}

void Player::handleInput()
{
  /* i think this has to go out of here. it's called at every frame.*/
  auto* animationComponent = getAnimationComponent();
  InputContextComponent inputContextComponent = getInputContextComponent();
  InputContext::Action action = inputContextComponent.getAction("forward");
  sf::Keyboard::Key forwardKey = SFMLKeyMap::toKey(action.key);

  AnimationComponent asd = getAsd();

  if (!animationComponent)
  {
    spdlog::info("no animation component found");
    return;
  }

  bool wasMoving = isMoving;
  isMoving = false;

  if (sf::Keyboard::isKeyPressed(forwardKey))
  {
    isMoving = true;

    if (!wasMoving)
    {
      if (asd.getCurrentAnimationId() != GameConfig::AnimationStates::RUNNING)
      {
        animationComponent->play(GameConfig::AnimationStates::RUNNING);
      }
    }

    animationComponent->getSprite().move(sf::Vector2f(3.0f, 0.0f));
  }
  else
  {
    if (wasMoving)
    {
      if (animationComponent->getCurrentAnimationId() !=
          GameConfig::AnimationStates::IDLE)
      {
        animationComponent->play(GameConfig::AnimationStates::IDLE);
      }
    }
  }
}
