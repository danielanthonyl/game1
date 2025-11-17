#pragma once

#include "box2d/box2d.h"
#include "vector"

class World;

class PhysicsComponent {
public:

  PhysicsComponent();

  b2BodyId createBody(b2BodyType bodyType, const b2Vec2& position, World* world);

  /**
   * DEBT!
   * these functions will be replaced.
   * there will be a class for each shape.
   */
  void createBox(const float width, const float height, const float friction);
  void createChain(const std::vector<b2Vec2> points);

  void setTransform(const b2Vec2& position);
  void setVelocity(const b2Vec2& position);

  b2Vec2 getPosition();

private:

b2BodyId bodyId;

};
