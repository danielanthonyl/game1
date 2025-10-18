#pragma once

#include <string>

// DEBT!  dependency injection. maybe use forward declaraction.
#include "Components/AnimationComponent.hpp"
#include "Components/InputContextComponent.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "box2d/box2d.h"

class World;

class Entity
{
  friend class World;

 public:

  virtual ~Entity() = default;
  explicit Entity();

  void initialize();

  virtual void update(float deltaTime);

  virtual void draw(sf::RenderWindow& target);

  static Entity* create(const std::string& name);

  template<typename T>
  static bool registerType(const std::string& name)
  {
    getRegistry()[name] = []() -> Entity* {return new T(); };
    return true;
  }

  const sf::Vector2f& getPosition() const;

  AnimationComponent& getAnimationComponent();

  InputContextComponent& getInputContextComponent();

  sf::Sprite &getSprite();
  const sf::Sprite &getSprite() const;

  const World* getWorld() const;

  void setPosition(const sf::Vector2f& newPosition);

 private:
  using CreatorFunc = Entity*(*)();
  static std::map<std::string, CreatorFunc>& getRegistry();


  void setWorld(World* worldPtr);

  World* world = nullptr;
  sf::Vector2f position;
  AnimationComponent animationComponent;
  InputContextComponent inputContextComponent;
  sf::Sprite sprite;
  sf::Texture defaultTexture;
  b2BodyId bodyId;

  constexpr static float PIXELS_PER_METER = 5.0f;

 protected:
  virtual void setupPlayerComponent();
};

#define REGISTER_ENTITY(ClassName) \
  static bool ClassName##_registered = Entity::registerType<ClassName>(#ClassName)