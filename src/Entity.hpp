#pragma once

#include <memory>
#include <string>

#include "SFML/Graphics.hpp"

// DEBT!  dependency injection
#include "AnimationComponent.hpp"
#include "InputComponent.hpp"

class Entity {
 public:
  explicit Entity(const std::string& id);

  virtual void update(float deltaTime);

  virtual void draw(sf::RenderTarget& target);

  AnimationComponent& addAnimationComponent();
  InputComponent& addInputComponent();

  // getters/setters
  const std::string& getId() const;
  const sf::Vector2f& getPosition() const;
  AnimationComponent* getAnimationComponent();
  InputComponent* getInputComponent();

  void setPosition(const sf::Vector2f& newPosition);

 private:
  std::string id;
  sf::Vector2f position;
  std::unique_ptr<AnimationComponent> animationComponent;
  std::unique_ptr<InputComponent> inputComponent;
};
