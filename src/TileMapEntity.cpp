#include "TileMapEntity.hpp"

#include "GameConfig.hpp"
#include "spdlog/spdlog.h"

TileMapEntity::TileMapEntity() : Entity()
{
  name = "tile";
  bodyType = BodyTypes::Static;
  width = 100.0f;
  height = 100.0f;
  friction = 1.0f;
  getAnimationComponent().setTexture("tile");
}

void TileMapEntity::initialize()
{
  Entity::initialize();

  setPivotPoint(PivotPoints::TopCenter);
  createChain();

}

void TileMapEntity::draw(sf::RenderWindow& target)
{
  // Entity::draw(target);

  tileMapComponent.draw(target);
}

void TileMapEntity::setTilePosition(sf::Vector2f& position)
{
  setPosition(position);
}

TileMapComponent& TileMapEntity::getTileMapComponent()
{
  return tileMapComponent;
}
