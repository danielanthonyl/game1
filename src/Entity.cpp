#include "Entity.hpp"

#include "SFML/Graphics/RenderTarget.hpp"
#include "spdlog/spdlog.h"
#include "World.hpp"

Entity::Entity()
  : position(0.0f, 0.0f), sprite(defaultTexture)
{
  sprite.setTexture(defaultTexture);
}

void Entity::initialize() {
  if (world == nullptr)
  {
    // DEBT! missing member name
    spdlog::error("entity {} not attached to a world.", "player");
    return;
  }

  //DEBT! debug
  applyTexture();
  // sprite.scale(initialScale);

  width = sprite.getGlobalBounds().size.x / PIXELS_PER_METER;
  height = sprite.getGlobalBounds().size.y / PIXELS_PER_METER;

  b2BodyDef bodyDef = b2DefaultBodyDef();
  bodyDef.type = bodyType;
  bodyDef.position = initialPosition;
  bodyId = b2CreateBody(world->getPhysicsWorldId(), &bodyDef);

  // create body collision shape
  b2Polygon dynamicBox = b2MakeBox(
    width / 2.0f, height / 2.0f);

  b2ShapeDef shapeDef = b2DefaultShapeDef();
  shapeDef.material.friction = 0.3f;
  shapeDef.density = 1.0f;
  b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);

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

  applyTexture();

  // physics handler
  // b2Vec2 bodyPos = b2Body_GetPosition(bodyId);
  // sf::Vector2 pos(bodyPos.x * PIXELS_PER_METER, bodyPos.y * PIXELS_PER_METER);
  // sprite.setPosition(pos);
  // rectangle.setPosition(pos);
  // rectangle.setPosition({ bodyPos.x , bodyPos.y });

  // input handler
  inputContextComponent.handleInput();
}

void Entity::draw(sf::RenderWindow& renderWindow)
{
  b2Vec2 bodyPos = b2Body_GetPosition(bodyId);
  sf::Vector2f pos(bodyPos.x * PIXELS_PER_METER, bodyPos.y * PIXELS_PER_METER);

  sf::Vector2f size = { width * PIXELS_PER_METER, height * PIXELS_PER_METER };

  rectangle.setSize(size);
  rectangle.setOrigin({ size.x / 2, size.y / 2 });
  rectangle.setPosition(pos);
  rectangle.setOutlineColor(sf::Color::Red);
  rectangle.setFillColor(sf::Color::Transparent);
  rectangle.setOutlineThickness(1);
  renderWindow.draw(rectangle);

  // sprite
  getSprite().setOrigin({ size.x / 2, size.y / 2 });
  getSprite().setPosition(pos);
  renderWindow.draw(getSprite());
}

std::map<std::string, Entity::CreatorFunc>& Entity::getRegistry()
{
  static std::map<std::string, CreatorFunc> registry;
  return registry;
}

std::unique_ptr<Entity> Entity::create(const std::string& name)
{
  // DEBT! implement getName();
  auto it = getRegistry().find(name);
  if (it == getRegistry().end()) return nullptr;

  return std::unique_ptr<Entity>(it->second());
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
  sprite.setPosition(position);

  b2Vec2 pos(position.x, position.y);
  b2Body_SetLinearVelocity(bodyId, pos);
  // b2Body_SetTransform(bodyId, pos, b2Body_GetRotation(bodyId));
}

void Entity::applyTexture()
{
  if (animationComponent.getCurrentTextureId() != lastTextureId)
  {
    sprite.setTexture(animationComponent.getCurrentTexture());
    lastTextureId = animationComponent.getCurrentTextureId();
  }

  if (animationComponent.getCurrentFrameInt() != lastFrameInt)
  {
    sprite.setTextureRect(animationComponent.getCurrentFrameRect());
    lastFrameInt = animationComponent.getCurrentFrameInt();
  }
}
