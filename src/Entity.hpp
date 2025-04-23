#pragma once

#include <memory>
#include <string>

// DEBT!  dependency injection
#include "AnimationComponent.hpp"
#include "InputContextComponent.hpp"

class Entity
{
 public:
  explicit Entity(const std::string& id);

  virtual void update(float deltaTime);

  virtual void draw(sf::RenderTarget& target);

  AnimationComponent& addAnimationComponent();

  // getters/setters
  const std::string& getId() const;
  const sf::Vector2f& getPosition() const;
  AnimationComponent* getAnimationComponent();
  InputContextComponent& getInputContextComponent();

  void setPosition(const sf::Vector2f& newPosition);

 private:
  std::string id;
  sf::Vector2f position;
  // no need unique_ptr here
  std::unique_ptr<AnimationComponent> animationComponent;
  InputContextComponent inputContextComponent;
};
