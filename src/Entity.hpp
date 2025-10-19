/**
 * DEBT! Entity will be split into SpriteComponent for handling texture management, rendering etc.
 */

#pragma once

#include <string>

// DEBT!  dependency injection. maybe use forward declaraction.
#include "Components/AnimationComponent.hpp"
#include "Components/InputContextComponent.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "box2d/box2d.h"
#include <SFML/Graphics/RectangleShape.hpp>

class World;

struct BodyTypes {
  constexpr static b2BodyType Static = b2_staticBody;
  constexpr static b2BodyType Dynamic = b2_dynamicBody;
};

class Entity
{
  friend class World;

public:
  virtual ~Entity() = default;
  explicit Entity();

  void initialize();

  virtual void update(float deltaTime);

  virtual void draw(sf::RenderWindow& target);

  static std::unique_ptr<Entity> create(const std::string& name);

  template<typename T>
  static bool registerType(const std::string& name)
  {
    getRegistry()[name] = []() -> std::unique_ptr<Entity> { return std::make_unique<T>(); };
    return true;
  }

  const sf::Vector2f& getPosition() const;

  AnimationComponent& getAnimationComponent();

  InputContextComponent& getInputContextComponent();

  sf::Sprite& getSprite();
  const sf::Sprite& getSprite() const;

  const World* getWorld() const;

  void setPosition(const sf::Vector2f& newPosition);

private:
  constexpr static float PIXELS_PER_METER = 100.0f;
  using CreatorFunc = std::function<std::unique_ptr<Entity>()>;

  // DEBUG
  sf::RectangleShape rectangle;
  void applyTexture();

  // components
  AnimationComponent animationComponent;
  InputContextComponent inputContextComponent;

  World* world = nullptr;
  sf::Vector2f position;
  sf::Sprite sprite;

  b2BodyId bodyId;

  sf::Texture defaultTexture;
  std::string lastTextureId;
  size_t lastFrameInt;

  void setWorld(World* worldPtr);
  static std::map<std::string, CreatorFunc>& getRegistry();

protected:
  // DEBUG
  std::string name;
  float width = 41.0f;
  float height = 48.0f;

  b2BodyType bodyType = BodyTypes::Dynamic;
  b2Vec2 initialPosition = {0.0f, 0.0f};
  sf::Vector2f initialScale = {1.0f, 1.0f};

  virtual void setupPlayerComponent();
};

#define REGISTER_ENTITY(ClassName) \
  static bool ClassName##_registered = Entity::registerType<ClassName>(#ClassName)