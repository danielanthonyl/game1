#pragma once

#include "Entity.hpp"
#include "DataObjects/Tileset.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Components/TileMapComponent.hpp"

class TileMapEntity : public Entity
{
public:
  explicit TileMapEntity();

  void initialize() override;

  void draw(sf::RenderWindow& target) override;

  void setTilePosition(sf::Vector2f& position);

  TileMapComponent& getTileMapComponent();

private:
  TileLayer* tileLayer;
  TileMapComponent tileMapComponent;
};

REGISTER_ENTITY(TileMapEntity);