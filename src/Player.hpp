#pragma once

#include <string>

#include "Entity.hpp"

class Player : public Entity
{
 public:
  explicit Player(const std::string &id);

  void update(float deltaTime) override;

  void initializeAnimations();

 private:
  void handleInput();
  bool isMoving = false;
};
