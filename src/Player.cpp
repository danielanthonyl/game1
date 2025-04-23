#include "Player.hpp"

Player::Player(const std::string& id) : Entity(id) { initializeAnimations(); }

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
  auto* animationComponent = getAnimationComponent();
  if (!animationComponent)
  {
    spdlog::error("Animation component not found");
    return;
  }

  bool wasMoving = isMoving;
  isMoving = false;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
  {
    isMoving = true;

    if (!wasMoving)
    {
      if (animationComponent->getCurrentAnimationId() !=
          GameConfig::AnimationStates::RUNNING)
      {
        animationComponent->play(GameConfig::AnimationStates::RUNNING);
      }
    }
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
