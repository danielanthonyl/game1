#include "Game.hpp"


Game::Game(const std::string& title, unsigned int width, unsigned int height)
  : window(sf::VideoMode({ width, height }), title)
{
  // DEBT! frame rate stuff
  window.setFramerateLimit(60);
}

void Game::initialize()
{
  auto& resourceManager = ResourceManager::getInstance();

  //DEBT! debug.
  resourceManager.loadTextureAsset("tile", "./tile.png", "./tile.json");

  resourceManager.loadTextureAsset(
    GameConfig::ResourceIds::PLAYER_IDLE,
    GameConfig::ResourcePaths::PLAYER_IDLE_TEXTURE,
    GameConfig::ResourcePaths::PLAYER_IDLE_TEXTURE_DATA);

  resourceManager.loadTextureAsset(
    GameConfig::ResourceIds::PLAYER_RUNNING,
    GameConfig::ResourcePaths::PLAYER_RUNNING_TEXTURE,
    GameConfig::ResourcePaths::PLAYER_RUNNING_TEXTURE_DATA);

  // DEBT! debug. This should come from file - data driven
  std::vector<EntitySpawnParameters> entities{
    {"Player", {1.0f, 2.0f}},
    {"Tile",   {2.0f, 4.0f}},
    {"Tile",   {4.7f, 4.0f}}
  };

  world.spawnEntities(entities);

  spdlog::info("Game initialized.");
}

void Game::run()
{
  running = true;
  while (running && window.isOpen())
  {
    processEvents();

    float deltaTime = clock.restart().asSeconds();
    update(deltaTime);

    render();
  }
}

void Game::processEvents()
{
  while (const std::optional event = window.pollEvent())
  {
    if (event->is<sf::Event::Closed>())
    {
      window.close();
      running = false;
    }
  }
}

void Game::update(float deltaTime)
{
  world.update(deltaTime);
}

void Game::render()
{
  window.clear(sf::Color::White);

  world.render(window);

  window.display();
}

Entity& Game::addEntity(std::unique_ptr<Entity> entity)
{
  Entity& entityRef = *entity;
  entities.push_back(std::move(entity));
  return entityRef;
}

