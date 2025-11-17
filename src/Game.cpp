#include "Game.hpp"

#include "TileMapEntity.hpp"


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
  resourceManager.loadTileSetAsset("level1", "./level1.json");

  resourceManager.loadTextureAsset(
    GameConfig::ResourceIds::PLAYER_IDLE,
    GameConfig::ResourcePaths::PLAYER_IDLE_TEXTURE,
    GameConfig::ResourcePaths::PLAYER_IDLE_TEXTURE_DATA);

  resourceManager.loadTextureAsset(
    GameConfig::ResourceIds::PLAYER_RUNNING,
    GameConfig::ResourcePaths::PLAYER_RUNNING_TEXTURE,
    GameConfig::ResourcePaths::PLAYER_RUNNING_TEXTURE_DATA);

  // DEBT! debug. This should come from file - data driven
  // spawn tiles
  std::vector<std::unique_ptr<TileInfo>> tiles;

  constexpr std::nullopt_t null = std::nullopt;
  std::vector<std::optional<size_t>> tileMap = {
    null, null, null, null, null, null, null, null, null, null, null, null,
    null, null, null, null, null, null, null, null, null, null, null, null,
    null, null, null, null, null, null, null, null, null, null, null, null,
    null, null, null, null, null, null, null, null, null, null, null, null,
    null, null, null, null, null, null, null, null, null, null,  390, null,
       0,    1,    2,    3,    4, null,    0,    1,    2,    3,    4, null,
      25,   26,   27,   28,   29, null,   25,   26,   27,   28,   29, null,
     100,  101,  102,  103,  104, null,  100,  101,  102,  103,  104, null,
  };

  for (auto& tileIndex : tileMap)
  {
    std::unique_ptr<TileInfo> tileInfo;

    if (tileIndex.has_value())
    {
      tileInfo = std::make_unique<TileInfo>();
      tileInfo->tileIndex = *tileIndex;
      tileInfo->tileSet = resourceManager.getTileSet("level1");
    }

    tiles.push_back(std::move(tileInfo));
  }

  tileLayer = std::make_unique<TileLayer>();
  tileLayer->width = 12;
  tileLayer->height = 8;
  tileLayer->tiles = std::move(tiles);

  TileMapEntity* tile = world.spawnEntity<TileMapEntity>();
  tile->setPosition({ 0.0f, 0.0f });
  // tile->setTileMap(tileLayer.get());
  tile->getTileMapComponent().setTileMap(tileLayer.get());

  // spawn player
  std::vector<EntitySpawnParameters> entities{
    {"Player", {0.0f, 0.0f}},
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

