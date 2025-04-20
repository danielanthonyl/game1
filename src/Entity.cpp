#include "Entity.hpp"

Entity::Entity(const std::string &id)
  : id(id), position(0.0f, 0.0f)
{
}

void Entity::update(float deltaTime)
{
  if(animationComponent)
  {
    animationComponent->update(deltaTime);
  }

}

void Entity::draw(sf::RenderTarget& target)
{
  if(animationComponent)
  {
    target.draw(animationComponent->getSprite());
  }
}

AnimationComponent& Entity::addAnimationComponent()
{

  if(!animationComponent)
  {
    animationComponent = std::make_unique<AnimationComponent>();
  }

  return *animationComponent;
}


// getters
const std::string& Entity::getId() const
{
  return id;
}

const sf::Vector2f& Entity::getPosition() const
{
  return position;
}

AnimationComponent* Entity::getAnimationComponent()
{
  return animationComponent.get();
}

// setters
void Entity::setPosition(const sf::Vector2f& newPosition)
{
  position = newPosition;
}

