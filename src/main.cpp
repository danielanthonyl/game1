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

  Game game("Game 1", 800, 800); // light instantiation

  game.initialize(); // heavy operations
  game.run();

  spdlog::info("Game shutting down.");

  return 0;
}
