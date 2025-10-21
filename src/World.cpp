#include "World.hpp"
#include "spdlog/spdlog.h"
#include "SFML/Graphics.hpp"

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

void World::update(float deltaTime)
{
  updateWorld();
  updateEntities(deltaTime);
}

void World::updateWorld()
{
  b2World_Step(getPhysicsWorldId(), timeStep, subStepCount);
}

void World::updateEntities(float deltaTime)
{
  if (entities.empty()) return;

  for (std::unique_ptr<Entity>& entity : entities)
  {
    entity->update(deltaTime);
  }
}

void World::render(sf::RenderWindow& window)
{
  if (entities.empty()) return;

  for (std::unique_ptr<Entity>& entity : entities)
  {
    entity->draw(window);
  }
}

void World::spawnEntities(const std::vector<EntitySpawnParameters>& spawnParameters) {
  if (spawnParameters.empty())
  {
    spdlog::error("attempt to spawn empty entity");
    return;
  }

  for (const EntitySpawnParameters& entityParameter : spawnParameters)
  {
    std::unique_ptr<Entity> entity = Entity::create(entityParameter.name);
    entity->setWorld(this);
    entity->initialize();
    entity->setPosition(entityParameter.coordinates);
    entities.push_back(std::move(entity));
  }
}

void World::spawnEntity(const std::string& name)
{
  if (name.empty())
  {
    spdlog::error("attempt to spawn empty entity {}", name);
    return;
  }

  std::unique_ptr<Entity> entity = Entity::create(name);
  entity->setWorld(this);
  entity->initialize();
  entities.push_back(std::move(entity));
}