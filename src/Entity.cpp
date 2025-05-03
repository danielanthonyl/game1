#include "Entity.hpp"

#include "SFML/Graphics/RenderTarget.hpp"
#include "spdlog/spdlog.h"

Entity::Entity(const std::string& id) : id(id), position(0.0f, 0.0f) {}

void Entity::initialize() { setupPlayerComponent(); }

void Entity::setupPlayerComponent()
{
  spdlog::info("no actions or contexts bound to entity");
}

void Entity::update(float deltaTime)
{
  animationComponent.update(deltaTime);
  controllerComponent.handleInput(*this);
}

void Entity::draw(sf::RenderTarget& target)
{
  target.draw(animationComponent.getSprite());
}

// getters
const std::string& Entity::getId() const { return id; }

InputContextComponent& Entity::getInputContextComponent()
{
  return inputContextComponent;
}

const sf::Vector2f& Entity::getPosition() const { return position; }

AnimationComponent& Entity::getAnimationComponent()
{
  return animationComponent;
}

ControllerComponent& Entity::getControllerComponent()
{
  return controllerComponent;
}

// setters
void Entity::setPosition(const sf::Vector2f& newPosition)
{
  position = newPosition;
}
