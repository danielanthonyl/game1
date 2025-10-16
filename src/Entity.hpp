#pragma once

#include <string>

// DEBT!  dependency injection. maybe use forward declaraction.
#include "Components/AnimationComponent.hpp"
#include "Components/InputContextComponent.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Entity
{
 public:
  explicit Entity(const std::string& id);

  void initialize();

  virtual void update(float deltaTime);

  virtual void draw(sf::RenderWindow& target);

  // getters/setters
  const std::string& getId() const;

  const sf::Vector2f& getPosition() const;

  AnimationComponent& getAnimationComponent();

  InputContextComponent& getInputContextComponent();

  sf::Sprite &getSprite();

  const sf::Sprite &getSprite() const;

  void setPosition(const sf::Vector2f& newPosition);

 private:
  std::string id;
  sf::Vector2f position;
  AnimationComponent animationComponent;
  InputContextComponent inputContextComponent;
  sf::Sprite sprite;
  sf::Texture defaultTexture;

 protected:
  virtual void setupPlayerComponent();
};
