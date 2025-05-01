#include <memory>

#include "Game.hpp"
#include "Player.hpp"
#include "nlohmann/json.hpp"
#include "spdlog/spdlog.h"

using json = nlohmann::json;

int main()
{
  spdlog::set_level(spdlog::level::info);
  spdlog::info("Starting Game1");

  Game game("Game 1", 800, 800);

  game.initialize();

  auto player = std::make_unique<Player>("player1");
  game.addEntity(std::move(player));

  game.run();

  spdlog::info("Game shutting down.");

  return 0;
}
