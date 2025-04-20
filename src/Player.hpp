#pragma once

#include <string>

#include "Entity.hpp"
#include "ResourceManager.hpp"
#include "GameConfig.hpp"
#include "spdlog/spdlog.h"


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
