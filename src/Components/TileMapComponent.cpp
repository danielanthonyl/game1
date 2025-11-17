#include "TileMapComponent.hpp"
#include "PhysicsComponent.hpp"

void TileMapComponent::initilise()
{
  initialiseSprites();
}

void TileMapComponent::draw(sf::RenderWindow& target)
{
  if (sprites.empty())
  {
    spdlog::error("texture is empty. No sprites to draw.");
    return;
  }

  for (auto& sprite : sprites)
  {
    if (!sprite)
    {
      spdlog::error("sprite is null");
      continue;
    }

    target.draw(*sprite);
  }
}

void TileMapComponent::setTileMap(TileLayer* tileLayerPtr)
{
  if (tileLayerPtr == nullptr)
  {
    spdlog::error("tileMap is null.");
    return;
  };

  tileLayer = tileLayerPtr;

  // DEBT!
  initialiseSprites();
  initialiseCollisions();
}

void TileMapComponent::initialiseSprites()
{
  if (tileLayer == nullptr)
  {
    spdlog::error("tile layer is null.");
    return;
  }

  sprites.clear();
  sprites.reserve(tileLayer->tiles.size());

  float scaleFactor = 3.0f;

  for (size_t index = 0; index < tileLayer->tiles.size(); index++)
  {
    auto& tile = tileLayer->tiles[index];

    // null tiles just mean empty spaces at the grid.
    if (!tile) continue;

    // DEBT! batch/vertex array
    auto sprite = std::make_unique<sf::Sprite>(*tile->tileSet->texture);

    // rect cut
    float meterPerPixels = 100.0f;
    int tileIndex = static_cast<int>(tile->tileIndex);
    IntVector tileSize = tile->tileSet->tileSize;       // in pixels
    IntVector tileSetSize = tile->tileSet->tileSetSize; // in tiles

    int tileWidth = tileSize.width;            // in pixels
    int tileHeight = tileSize.height;          // in pixels
    int tileSetWidth = tileSetSize.width;      // in tiles
    int tileSetHeight = tileSetSize.height;    // in tiles

    int rectColumn = tileIndex % tileSetWidth; // index
    int rectRow = tileIndex / tileSetWidth;    // index

    int rectX = rectColumn * tileWidth;  // in pixels
    int rectY = rectRow * tileHeight;    // in pixels

    sprite->setTextureRect(
      sf::IntRect({ rectX, rectY }, { tileWidth, tileHeight })
    );

    sprite->scale({ scaleFactor, scaleFactor });

    // position
    float layerColumn = static_cast<float>(index % tileLayer->width); // index
    float layerRow = static_cast<float>(index / tileLayer->width);    // index
    sprite->setPosition({
      (layerColumn * tileWidth) * scaleFactor,
      (layerRow * tileHeight) * scaleFactor });

    sprites.push_back(std::move(sprite));
  }
}

void TileMapComponent::initialiseCollisions()
{
  if (owner == nullptr)
  {
    spdlog::error("entity is null. Can't proceed creating collisions");
    return;
  }

  // do things

  float currentSegment = 0.0f;
  std::vector<b2Vec2> vect;

  for (size_t index = 0; index < tileLayer->tiles.size(); index++)
  {
    auto& tile = tileLayer->tiles[index];

    if (tile == nullptr) {

      currentSegment = 0.0f;
      continue;
    }

    float layerColumn = static_cast<float>(index % tileLayer->width);
    float layerRow = static_cast<float>(index / tileLayer->width);


    currentSegment += tile->tileSet->tileSize.width;
  }

  // make a box instead of a chain.
  owner->getPhysicsComponent().createChain({
      {-20.0f, 3.0f},
      {-5.0f, 3.0f},
      {5.0f, 3.0f},
      {20.0f, 3.0f},
    });
}


void TileMapComponent::setOwner(Entity* entity)
{
  if (entity == nullptr)
  {
    spdlog::error("entity is null.");
    return;
  };

  owner = entity;
}

Entity* TileMapComponent::getOwner()
{
  return owner;
}


