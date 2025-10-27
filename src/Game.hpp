#pragma once

#include <memory>
#include <optional>

//DEBT! dependency injection
#include "ResourceManager.hpp"
#include "GameConfig.hpp"
#include "spdlog/spdlog.h"
#include "SFML/Graphics.hpp"
#include "Entity.hpp"
#include "World.hpp"
#include "box2d/box2d.h"

class Game
{
public:
  Game(const std::string& title, unsigned int width, unsigned int height);

  void initialize();
  void run();

  Entity& addEntity(std::unique_ptr<Entity> entity);

private:
  // DEBT! debug. (should) be temporary
  std::unique_ptr<TileLayer> tileLayer;

  void render();
  void update(float deltaTime);
  void processEvents();

  World world;

  bool running = false;
  sf::Clock clock;
  sf::RenderWindow window;
  std::vector<std::unique_ptr<Entity>> entities;
};
