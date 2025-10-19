#pragma once

#include "Entity.hpp"
#include "box2d/box2d.h"
#include "SFML/Graphics/RenderWindow.hpp"

class World {
public:
  explicit World();

  ~World();

  // void initialize();

  void update(float deltaTime);
  void render(sf::RenderWindow& window);

  void spawnEntity(std::unique_ptr<Entity> entity);
  void spawnEntity(const std::string& name);


  void update();

  const b2WorldId getPhysicsWorldId() const;

  private:
  std::vector<std::unique_ptr<Entity>> entities;
  b2WorldId worldId;
  // DEBT! see how and where to apply these frame rate related stuff.
  // for game loop frame rate, animations, physics etc..
  float timeStep = 1.0f / 60.0f;
  int subStepCount = 4;

  void updateWorld();
  void updateEntities(float deltaTime);
};