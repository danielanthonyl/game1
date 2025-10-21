#pragma once
#include "Entity.hpp"

class Tile : public Entity
{
public:
  explicit Tile();

  void initialize() override;

  void setTilePosition(sf::Vector2f& position);

};

REGISTER_ENTITY(Tile);