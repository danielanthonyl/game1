#pragma once

#include <string>

#include "Entity.hpp"
#include "GameConfig.hpp"
#include "InputManager.hpp"
#include "ResourceManager.hpp"
#include "spdlog/spdlog.h"


class Player : public Entity {
 public:
  explicit Player(const std::string &id);

  void update(float deltaTime) override;

  void initializeAnimations();
  void setupPlayerInput();

 private:
  // Input action handlers
  void moveRight();
  void stopMoving();

  bool isMoving = false;
};
