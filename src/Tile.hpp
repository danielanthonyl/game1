#pragma once
#include "Entity.hpp"

class Tile : public Entity
{
public:
  explicit Tile();
};

REGISTER_ENTITY(Tile);