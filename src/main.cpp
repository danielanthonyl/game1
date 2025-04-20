#include <stdio.h>

#include <fstream>
#include <iostream>
#include <memory>

#include "AnimationData.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SpriteAnimator.hpp"
#include "spdlog/spdlog.h"
#include "nlohmann/json.hpp"
#include "Game.hpp"
#include "Player.hpp"

using json = nlohmann::json;

int main() {
  spdlog::set_level(spdlog::level::info);
  spdlog::info("Starting Game1");

  Game game("Game 1", 800, 800);

  game.initialize();

  auto player = std::make_unique<Player>("player1");
  /* i think this is not necessary */
  player->setPosition({0.0f, 0.0f});
  game.addEntity(std::move(player));

  game.run();

  spdlog::info("Game shutting down.");
  return 0;


}
