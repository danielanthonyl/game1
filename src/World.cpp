#include "World.hpp"

World::World()
{
  b2WorldDef worldDef = b2DefaultWorldDef();
  worldDef.gravity = { 0.0f, 10.0f };
  worldId = b2CreateWorld(&worldDef);
}

World::~World()
{
  b2DestroyWorld(worldId);
}

const b2WorldId World::getPhysicsWorldId() const
{
  return worldId;
}

void World::update()
{
  b2World_Step(getPhysicsWorldId(), timeStep, subStepCount);
}

// void World::initialize()
// {
//   // create world
//   // // create ground box
//   // b2BodyDef groundBodyDef = b2DefaultBodyDef();
//   // groundBodyDef.position = { 0.0f, 40.0f };
//   // groundId = b2CreateBody(worldId, &groundBodyDef);

//   // // create ground collision shape
//   // b2Polygon groundBox = b2MakeBox(50.0f, 10.0f);
//   // b2ShapeDef groundShapeDef = b2DefaultShapeDef();
//   // b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

// }

void World::spawnEntity(Entity* entity) {
  entity->setWorld(this);
  entity->initialize();
  entities.push_back(entity);
}