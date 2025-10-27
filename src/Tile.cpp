#include "Tile.hpp"

#include "GameConfig.hpp"
#include "spdlog/spdlog.h"

Tile::Tile() : Entity()
{
  name = "tile";
  bodyType = BodyTypes::Static;
  width = 100.0f;
  height = 100.0f;
  friction = 1.0f;
  getAnimationComponent().setTexture("tile");
}

void Tile::initialize()
{
  Entity::initialize();

  setPivotPoint(PivotPoints::TopCenter);
  createChain();

}


void Tile::draw(sf::RenderWindow& target)
{
  // Entity::draw(target);

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

void Tile::setTilePosition(sf::Vector2f& position)
{
  setPosition(position);
}

void Tile::setTileMap(TileLayer* tileLayerPtr)
{
  if (tileLayerPtr == nullptr)
  {
    spdlog::error("tileMap is null.");
    return;
  };

  tileLayer = tileLayerPtr;

  initialiseSprites();
}

void Tile::initialiseSprites()
{
  if (tileLayer == nullptr)
  {
    spdlog::error("tile layer is null.");
    return;
  }

  for (auto& tile : tileLayer->tiles)
  {
    auto sprite = std::make_unique<sf::Sprite>(*tile->tileSet->texture);

    float meterPerPixels = 100.0f;
    size_t tileIndex = tile->tileIndex;
    IntVector tileSize = tile->tileSet->tileSize;

    int width = tileSize.width;
    int height = tileSize.height;

    int x = static_cast<int>(tileIndex * width);
    int y = static_cast<int>(0);

    sprite->setTextureRect(
      sf::IntRect({ x, y }, { width, height })
    );

    sprite->scale({5.0f, 5.0f});
    sprite->setPosition({static_cast<float>(x * 5), 0.0f});

    sprites.push_back(std::move(sprite));
  }
}
