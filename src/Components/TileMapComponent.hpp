#pragma once

#include "../Entity.hpp"
#include "../DataObjects/Tileset.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "box2d/box2d.h"

class TileMapComponent
{
  public:
  void initilise();

  void draw(sf::RenderWindow& target);

  // DEBT! should accept tile map when it exists.
  void setTileMap(TileLayer* tileLayerPtr);

  void setOwner(Entity* entity);
  Entity* getOwner();

  protected:
  Entity* owner;

  private:
  void initialiseSprites();
  void initialiseCollisions();

  // DEBT! should be a vector of tilelayers - a tilemap.
  TileLayer* tileLayer;
  std::vector<std::unique_ptr<sf::Sprite>> sprites;
  std::vector<b2Vec2> collisions;

};
