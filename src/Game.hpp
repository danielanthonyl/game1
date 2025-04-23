#pragma once

#include <memory>
#include <optional>

// DEBT! dependency injection
#include "Entity.hpp"
#include "GameConfig.hpp"
#include "InputManager.hpp"
#include "ResourceManager.hpp"
#include "SFML/Graphics.hpp"
#include "spdlog/spdlog.h"


class Game {
 public:
  Game(const std::string& title, unsigned int width, unsigned int height);

  void initialize();
  void run();

  Entity& addEntity(std::unique_ptr<Entity> entity);

  /* Getters */
  Entity* getEntity(const std::string& entityId);

 private:
  void render();
  void update(float deltaTime);
  void processEvents();

  bool running = false;
  sf::Clock clock;
  sf::RenderWindow window;
  std::vector<std::unique_ptr<Entity>> entities;
};
