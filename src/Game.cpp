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

  resourceManager.loadTextureAsset(
    GameConfig::ResourceIds::PLAYER_IDLE,
    GameConfig::ResourcePaths::PLAYER_IDLE_TEXTURE,
    GameConfig::ResourcePaths::PLAYER_IDLE_TEXTURE_DATA);

  resourceManager.loadTextureAsset(
    GameConfig::ResourceIds::PLAYER_RUNNING,
    GameConfig::ResourcePaths::PLAYER_RUNNING_TEXTURE,
    GameConfig::ResourcePaths::PLAYER_RUNNING_TEXTURE_DATA);

  // DEBT! debug. This should come from file - data driven
  player = Entity::create("Player");
  world.spawnEntity(player);

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
  // for (auto& entity : entities)
  // {
  //   entity->update(deltaTime);
  // }

  world.update();
  player->update(deltaTime);
}

void Game::render()
{
  window.clear(sf::Color::White);

  // b2Vec2 position = b2Body_GetPosition(bodyId);
  // b2Rot rotation = b2Body_GetRotation(bodyId);

  // sf::RectangleShape rectangle;
  // rectangle.setSize(sf::Vector2f(2.0f, 2.0f));
  // rectangle.setOutlineColor(sf::Color::Red);
  // rectangle.setOutlineThickness(5);
  // rectangle.setPosition({ position.x, position.y });
  // window.draw(rectangle);

  // for (auto& entity : entities)
  // {
  //   entity->draw(window);
  // }

  player->draw(window);

  window.display();
}

Entity& Game::addEntity(std::unique_ptr<Entity> entity)
{
  Entity& entityRef = *entity;
  entities.push_back(std::move(entity));
  return entityRef;
}

