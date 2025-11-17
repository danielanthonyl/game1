/**
 * DEBT! Entity will be split into SpriteComponent for handling texture management, rendering etc.
 */

#pragma once

#include <string>

 // DEBT!  dependency injection. maybe use forward declaraction.
#include "Components/AnimationComponent.hpp"
#include "Components/InputContextComponent.hpp"
#include "Components/PhysicsComponent.hpp"

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "box2d/box2d.h"
#include <SFML/Graphics/RectangleShape.hpp>

class World;

struct BodyTypes {
  constexpr static b2BodyType Static = b2_staticBody;
  constexpr static b2BodyType Dynamic = b2_dynamicBody;
};

enum PivotPoints
{
  TopLeft,
  TopCenter,
  CenterCenter,
  BottomCenter
};

class Entity
{
  friend class World;

public:
  virtual ~Entity() = default;
  explicit Entity();

  virtual void initialize();

  virtual void update(float deltaTime);

  virtual void draw(sf::RenderWindow& renderWindow);

  static std::unique_ptr<Entity> create(const std::string& name);

  template<typename T>
  static bool registerType(const std::string& name)
  {
    getRegistry()[name] = []() -> std::unique_ptr<Entity> { return std::make_unique<T>(); };
    return true;
  }

  const sf::Vector2f& getPosition() const;

  // DEBT! add controlled component - registry.
  // getComponent / setComponent template operations.
  AnimationComponent& getAnimationComponent();
  InputContextComponent& getInputContextComponent();
  PhysicsComponent& getPhysicsComponent();

  // DEBT! it should own the SceneComponent instead. The "RootComponent"
  // which defines the entity's transforms in the world.
  sf::Sprite& getSprite();
  const sf::Sprite& getSprite() const;

  const World* getWorld() const;

  void setPosition(const sf::Vector2f& newPosition);
  void addMovementInput(const sf::Vector2f& newPosition);
  void setPivotPoint(PivotPoints pivotPoint);

private:
  constexpr static float PIXELS_PER_METER = 100.0f;
  using CreatorFunc = std::function<std::unique_ptr<Entity>()>;

  // DEBUG
  sf::RectangleShape rectangle;
  void applyTexture();
  sf::Vector2f position = { 0.0f, 0.0f };
  sf::Vector2f pivotPoint;

  World* world = nullptr;
  sf::Sprite sprite;

  b2BodyId bodyId;

  sf::Texture defaultTexture;
  std::string lastTextureId;
  size_t lastFrameInt;

  void setWorld(World* worldPtr);
  static std::map<std::string, CreatorFunc>& getRegistry();

protected:
  // DEBUG - maybe getters/setters are more appropriate.
  std::string name;
  float width = 41.0f;
  float height = 48.0f;
  float friction = 1.0f;
  b2Vec2 initialPosition = { 0.0f, 0.0f };
  sf::Vector2f initialScale = { 1.0f, 1.0f };

  // components
  AnimationComponent animationComponent;
  InputContextComponent inputContextComponent;
  PhysicsComponent physicsComponent;

  b2BodyType bodyType = BodyTypes::Dynamic;

  virtual void setupPlayerComponent();

  /**
   * DEBT!
   * these functions will be replaced.
   * there will be a class for each shape.
   */
  void createBox();
  void createChain();
};

#define REGISTER_ENTITY(ClassName) \
  static bool ClassName##_registered = Entity::registerType<ClassName>(#ClassName)