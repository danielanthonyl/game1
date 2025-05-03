#pragma once

#include <string>

#include "Entity.hpp"

class Player : public Entity
{
 public:
  explicit Player(const std::string &id);

  void update(float deltaTime) override;
  void setupPlayerComponent() override;

  void initializeAnimations();

  // movements
  void moveForward();

 private:
  void handleInput();
  bool isMoving = false;
};
