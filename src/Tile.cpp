#include "Tile.hpp"

#include "GameConfig.hpp"

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

  // setPosition({2.0f, 4.0f});
}

void Tile::setTilePosition(sf::Vector2f& position)
{
  setPosition(position);
}