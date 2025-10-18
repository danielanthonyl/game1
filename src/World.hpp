#pragma once

#include "Entity.hpp"
#include "box2d/box2d.h"

class World {
public:
  explicit World();

  ~World();

  // void initialize();

  void spawnEntity(Entity* entity);
  void update();

  const b2WorldId getPhysicsWorldId() const;


  private:
  std::vector<Entity*> entities;
  b2WorldId worldId;
  // DEBT! see how and where to apply these frame rate related stuff.
  // for game loop frame rate, animations, physics etc..
  float timeStep = 1.0f / 60.0f;
  int subStepCount = 4;
};