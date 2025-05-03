#include "Game.hpp"

Game::Game(const std::string& title, unsigned int width, unsigned int height)
    : window(sf::VideoMode({width, height}), title)
{
  window.setFramerateLimit(60);
}

void Game::initialize()
{
  auto& resourceManager = ResourceManager::getInstance();

  resourceManager.loadTextureAsset(
      GameConfig::ResourceIds::PLAYER_IDLE,
      GameConfig::ResourcePaths::PLAYER_IDLE_TEXTURE,
      GameConfig::ResourcePaths::PLAYER_IDLE_TEXTURE_DATA);

  resourceManager.loadTextureAsset(
      GameConfig::ResourceIds::PLAYER_RUNNING,
      GameConfig::ResourcePaths::PLAYER_RUNNING_TEXTURE,
      GameConfig::ResourcePaths::PLAYER_RUNNING_TEXTURE_DATA);

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
  for (auto& entity : entities)
  {
    entity->update(deltaTime);
  }
}

void Game::render()
{
  window.clear(sf::Color::White);

  for (auto& entity : entities)
  {
    entity->draw(window);
  }

  window.display();
}

Entity& Game::addEntity(std::unique_ptr<Entity> entity)
{
  Entity& entityRef = *entity;
  entities.push_back(std::move(entity));
  return entityRef;
}

/* Getters */
Entity* Game::getEntity(const std::string& entityId)
{
  for (auto& entity : entities)
  {
    if (entity->getId() == entityId)
    {
      return entity.get();
    }
  }

  spdlog::warn("Entity {} not found.", entityId);
  return nullptr;
}
