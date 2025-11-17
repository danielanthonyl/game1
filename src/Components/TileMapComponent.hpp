#pragma once

#include "../DataObjects/Tileset.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class TileMapComponent
{
  public:
  void initilise();

  void draw(sf::RenderWindow& target);

  // DEBT! should accept tile map when it exists.
  void setTileMap(TileLayer* tileLayerPtr);

  private:
  void initialiseSprites();

  // DEBT! should be a vector of tilelayers - a tilemap.
  TileLayer* tileLayer;
  std::vector<std::unique_ptr<sf::Sprite>> sprites;

};
