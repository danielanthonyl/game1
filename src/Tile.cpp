#include "Tile.hpp"

#include "GameConfig.hpp"

Tile::Tile() : Entity()
{
  name = "tile";
  bodyType = BodyTypes::Static;
  width = 100.0f;
  height = 100.0f;
  initialPosition = {2.0f, 4.0f};

  getAnimationComponent().setTexture("tile");
}
