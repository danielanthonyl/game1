#include "Game.hpp"

#include "Tile.hpp"


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

  /**
   * Resource Manager -> load/unload json and png data for tilemaps [DONE]
   * Game -> instantiate resource manager and the TileMap data object.
   * TileMap -> creates a list of Tile each Tile would be another data object for each tile. (2 structs)
   * TileMapComponent -> grabs the TileMap and loop over rendering and handling collisions.
   * TileMapEntity -> owns all components and data object and orchestrate communication.
   */


   // DEBT! debug. This should come from file - data driven
  std::vector<EntitySpawnParameters> entities{
    {"Player", {3.0f, 0.0f}},
    // {"Tile",   {2.0f, 3.0f}},
    // {"Tile",   {4.7f, 4.0f}}
  };

  world.spawnEntities(entities);

  std::unique_ptr<TileInfo> tileInfo;
  tileInfo = std::make_unique<TileInfo>();
  tileInfo->tileIndex = 0;
  tileInfo->tileSet = resourceManager.getTileSet("level1");

  std::unique_ptr<TileInfo> tileInfo2;
  tileInfo2 = std::make_unique<TileInfo>();
  tileInfo2->tileIndex = 1;
  tileInfo2->tileSet = resourceManager.getTileSet("level1");

  std::unique_ptr<TileInfo> tileInfo3;
  tileInfo3 = std::make_unique<TileInfo>();
  tileInfo3->tileIndex = 2;
  tileInfo3->tileSet = resourceManager.getTileSet("level1");

  std::vector<std::unique_ptr<TileInfo>> tiles;
  tiles.push_back(std::move(tileInfo));
  tiles.push_back(std::move(tileInfo2));
  tiles.push_back(std::move(tileInfo3));

  tileLayer = std::make_unique<TileLayer>();
  tileLayer->height = 1;
  tileLayer->width = 1;
  tileLayer->tiles = std::move(tiles);

  Tile* tile = world.spawnEntity<Tile>();
  tile->setPosition({2.0f, 3.0f});
  tile->setTileMap(tileLayer.get());


  // DEBT! this should be "resourceManager.loadAsset<TileMap>()"
  // resourceManager.loadTileMapAsset("level-1", "level-1.json");
  // TileMapEntity tileMap;
  // tileMap.setWorld(this);
  // tileMap.setTileLayer(); // later it should be getRendercomponent().setTileMap(); instead.
  // tileMap.initialize();
  // tileMap.getRenderComponent().setTileMap(resourceManager.getTileMapAsset("level-1"));
  // world.spawnEntity(TileMap);

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

