#pragma once

#include "Entity.hpp"
#include "DataObjects/Tileset.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Tile : public Entity
{
public:
  explicit Tile();

  void initialize() override;

  void draw(sf::RenderWindow& target) override;

  void initialiseSprites();

  void setTilePosition(sf::Vector2f& position);

  // DEBT! should accept a TileMap when it exists.
  void setTileMap(TileLayer* tileLayerPtr);

private:
  TileLayer* tileLayer;
  std::vector<std::unique_ptr<sf::Sprite>> sprites;

};

REGISTER_ENTITY(Tile);