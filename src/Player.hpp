#pragma once

#include <string>

#include "Entity.hpp"
#include "box2d/box2d.h"

class Player : public Entity
{
 public:
  explicit Player();

  void initialize() override;

  void update(float deltaTime) override;
  void setupPlayerComponent() override;

  // movements
  void moveForward(InputContext::TriggerEvent event);

 private:
  bool isMoving = false;
};

REGISTER_ENTITY(Player);