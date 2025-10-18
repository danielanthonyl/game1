#include "Entity.hpp"

#include "SFML/Graphics/RenderTarget.hpp"
#include "spdlog/spdlog.h"
#include "World.hpp"

Entity::Entity()
  : position(0.0f, 0.0f), sprite(defaultTexture)
{
  sprite.setTexture(defaultTexture);

  //DEBT! debug
  sprite.scale({ 5.0f, 5.0f });
}

void Entity::initialize() {
  if (world != nullptr) {

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = { 0.0f, 0.0f };
    bodyId = b2CreateBody(world->getPhysicsWorldId(), &bodyDef);

    // create body collision shape
    b2Polygon dynamicBox = b2MakeBox(1.0f, 1.0f);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.material.friction = 0.3f;
    shapeDef.density = 1.0f;
    b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);

    // // create ground
    // b2BodyDef groundBodyDef = b2DefaultBodyDef();
    // groundBodyDef.position = { 0.0f, 300.0f };
    // b2BodyId groundId = b2CreateBody(world->getPhysicsWorldId(), &groundBodyDef);

    // // create ground collision shape
    // b2Polygon groundBox = b2MakeBox(50.0f, 10.0f);
    // b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    // b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);
  }

  setupPlayerComponent();
}

void Entity::setupPlayerComponent()
{
  spdlog::info("no actions or contexts bound to entity");
}

void Entity::update(float deltaTime)
{
  // animation handler
  animationComponent.update(deltaTime);
  sprite.setTexture(animationComponent.getCurrentTexture());
  sprite.setTextureRect(animationComponent.getCurrentFrameRect());

  // physics handler
  b2Vec2 bodyPos = b2Body_GetPosition(bodyId);
  sf::Vector2 pos(bodyPos.x * PIXELS_PER_METER, bodyPos.y * PIXELS_PER_METER);
  sprite.setPosition(pos);

  // input handler
  inputContextComponent.handleInput();
}

void Entity::draw(sf::RenderWindow& renderWindow)
{
  renderWindow.draw(getSprite());
}

std::map<std::string, Entity::CreatorFunc>& Entity::getRegistry()
{
  static std::map<std::string, CreatorFunc> registry;
  return registry;
}

Entity* Entity::create(const std::string& name)
{
  // DEBT! implement getName();
  auto it = getRegistry().find(name);
  if (it == getRegistry().end()) return nullptr;

  return it->second();
}

InputContextComponent& Entity::getInputContextComponent()
{
  return inputContextComponent;
}

const sf::Vector2f& Entity::getPosition() const { return position; }

AnimationComponent& Entity::getAnimationComponent()
{
  return animationComponent;
}

sf::Sprite& Entity::getSprite() { return sprite; }
const sf::Sprite& Entity::getSprite() const { return sprite; }

const World* Entity::getWorld() const
{
  return world;
}

void Entity::setWorld(World* worldPtr)
{
  world = worldPtr;
};

void Entity::setPosition(const sf::Vector2f& newPosition)
{
  position += newPosition;
  // sprite.setPosition(position);

  b2Vec2 pos(position.x, position.y);
  b2Body_SetLinearVelocity(bodyId, pos);
  // b2Body_SetTransform(bodyId, pos, b2Body_GetRotation(bodyId));
}
