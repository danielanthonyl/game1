#pragma once

#include <string>
#include <memory>

#include "SFML/Graphics.hpp"
// DEBT!  dependency injection
#include "AnimationComponent.hpp"

class Entity
{
public:
  explicit Entity(const std::string &id);

  virtual void update(float deltaTime);

  virtual void draw(sf::RenderTarget& target);

  AnimationComponent& addAnimationComponent();

  // getters/setters
  const std::string& getId() const;
  const sf::Vector2f &getPosition() const;
  AnimationComponent* getAnimationComponent();

  void setPosition(const sf::Vector2f& newPosition);

private:
  std::string id;
  sf::Vector2f position;
  std::unique_ptr<AnimationComponent> animationComponent;
};
