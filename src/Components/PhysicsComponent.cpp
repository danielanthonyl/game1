#include "PhysicsComponent.hpp"

#include "../World.hpp"

PhysicsComponent::PhysicsComponent()
{

}

b2BodyId PhysicsComponent::createBody(b2BodyType bodyType, const b2Vec2& position, World* world)
{
  b2BodyDef bodyDef = b2DefaultBodyDef();
  bodyDef.type = bodyType;
  bodyDef.position = position;
  bodyId = b2CreateBody(world->getPhysicsWorldId(), &bodyDef);

  if (!b2Body_IsValid(bodyId))
    spdlog::error("Body not created properly!");

  return bodyId;
}

void PhysicsComponent::createBox(const float width, const float height, const float friction)
{
  if (!b2Body_IsValid(bodyId))
  {
    spdlog::warn("skipping box creation. body is null.");
    return;
  };

  b2Polygon box = b2MakeBox(
    width / 2.0f, height / 2.0f);

  b2ShapeDef shape = b2DefaultShapeDef();
  shape.material.friction = friction;
  shape.density = 1.0f;
  shape.material.restitution = 0;
  b2CreatePolygonShape(bodyId, &shape, &box);
}

void PhysicsComponent::createChain(const std::vector<b2Vec2> points)
{
  if (!b2Body_IsValid(bodyId))
  {
    spdlog::warn("skipping chain creation. body is null.");
    return;
  };

  // static std::vector<b2Vec2> points = {
  //     {-20.0f, 0.0f},
  //     {-5.0f, 0.0f},
  //     {5.0f, 0.0f},
  //     {20.0f, 0.0f},
  // };

  b2ChainDef chainDef = b2DefaultChainDef();
  chainDef.count = points.size();
  chainDef.points = points.data();
  b2CreateChain(bodyId, &chainDef);
}

b2Vec2 PhysicsComponent::getPosition()
{
  if (!b2Body_IsValid(bodyId))
  {
    spdlog::warn("trying to get position of a null body.");
    return { 0.0f, 0.0f };
  };

  return b2Body_GetPosition(bodyId);
}

void PhysicsComponent::setTransform(const b2Vec2& position)
{
  if (!b2Body_IsValid(bodyId))
  {
    spdlog::warn("trying to transform null body.");
    return;
  }

  b2Body_SetTransform(bodyId, { position.x, position.y }, b2Body_GetRotation(bodyId));
}

void PhysicsComponent::setVelocity(const b2Vec2& position)
{
  if (!b2Body_IsValid(bodyId))
  {
    spdlog::warn("trying to set velocity on a null body.");
    return;
  }

  b2Body_SetLinearVelocity(bodyId, position);
}