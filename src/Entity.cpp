#include "Entity.hpp"

#include "SFML/Graphics/RenderTarget.hpp"
#include "spdlog/spdlog.h"
#include "World.hpp"

Entity::Entity() : sprite(defaultTexture)
{
  sprite.setTexture(defaultTexture);
}

void Entity::initialize() {
  if (world == nullptr)
  {
    spdlog::error("entity {} not attached to a world.", name);
    return;
  }

  //DEBT! debug
  applyTexture();

  // if the texture changes during animation, the physics body size needs to be updated.
  // DEBT! getting the box to be the size of the sprite is debug only.
  // default hitbox can be the default sprite size, but client subclasses can override this.
  sf::FloatRect local = sprite.getLocalBounds();
  sprite.setOrigin({ local.size.x / 2.f, local.size.y / 2.f });
  sprite.scale(initialScale);

  width = sprite.getGlobalBounds().size.x / PIXELS_PER_METER;
  height = sprite.getGlobalBounds().size.y / PIXELS_PER_METER;

  b2BodyDef bodyDef = b2DefaultBodyDef();
  bodyDef.type = bodyType;
  bodyDef.position = { position.x, position.y };
  bodyId = b2CreateBody(world->getPhysicsWorldId(), &bodyDef);

  // create body collision shape
  b2Polygon dynamicBox = b2MakeBox(
    width / 2.0f, height / 2.0f);

  b2ShapeDef shapeDef = b2DefaultShapeDef();
  shapeDef.material.friction = friction;
  shapeDef.density = 1.0f;
  shapeDef.material.restitution = 0;
  b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);

  setupPlayerComponent();
}

void Entity::setupPlayerComponent()
{
  spdlog::info("no actions or contexts bound to entity {}", name);
}

void Entity::update(float deltaTime)
{
  // animation handler
  animationComponent.update(deltaTime);

  applyTexture();

  // update physics
  if (b2Body_IsValid(bodyId))
  {
    b2Vec2 bodyPos = b2Body_GetPosition(bodyId);
    sf::Vector2f pos(bodyPos.x * PIXELS_PER_METER, bodyPos.y * PIXELS_PER_METER);
    getSprite().setPosition(pos);
    rectangle.setPosition(pos);
  };

  // update input
  inputContextComponent.handleInput();
}

void Entity::draw(sf::RenderWindow& renderWindow)
{
  sf::Vector2f size = { width * PIXELS_PER_METER, height * PIXELS_PER_METER };

  rectangle.setSize(size);
  rectangle.setOrigin({ size.x / 2, size.y / 2 });
  rectangle.setOutlineColor(sf::Color::Red);
  rectangle.setFillColor(sf::Color::Transparent);
  rectangle.setOutlineThickness(1);
  renderWindow.draw(rectangle);

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

void Entity::addMovementInput(const sf::Vector2f& newPosition)
{
  b2Vec2 pos(newPosition.x, newPosition.y);
  b2Body_SetLinearVelocity(bodyId, pos);
}

void Entity::setPosition(const sf::Vector2f& newPosition)
{
  position = newPosition;

  if (b2Body_IsValid(bodyId))
  {
    b2Body_SetTransform(bodyId, { position.x, position.y }, b2Body_GetRotation(bodyId));
  } else {
    spdlog::warn("{} not correctly initialized.", name);
  }
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
