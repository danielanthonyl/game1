#include "Player.hpp"

Player::Player(const std::string& id) : Entity(id) {
  initializeAnimations();
  setupPlayerInput();
}

void Player::update(float deltaTime) { Entity::update(deltaTime); }

void Player::initializeAnimations() {
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

void Player::setupPlayerInput() {
  auto& inputComponent = addInputComponent();
  auto& inputManager = InputManager::getInstance();

  // Bind actions to methods
  inputComponent.bindAction("MoveRight", [this]() { moveRight(); });
  inputComponent.bindActionReleased("MoveRight", [this]() { stopMoving(); });

  // Register the input component with the manager
  inputManager.registerComponent(getInputComponent());
}

void Player::moveRight() {
  auto* animationComponent = getAnimationComponent();
  if (!animationComponent) {
    spdlog::error("Animation component not found");
    return;
  }

  isMoving = true;

  if (animationComponent->getCurrentAnimationId() !=
      GameConfig::AnimationStates::RUNNING) {
    animationComponent->play(GameConfig::AnimationStates::RUNNING);
  }
}

void Player::stopMoving() {
  auto* animationComponent = getAnimationComponent();
  if (!animationComponent) {
    spdlog::error("Animation component not found");
    return;
  }

  isMoving = false;

  if (animationComponent->getCurrentAnimationId() !=
      GameConfig::AnimationStates::IDLE) {
    animationComponent->play(GameConfig::AnimationStates::IDLE);
  }
}
