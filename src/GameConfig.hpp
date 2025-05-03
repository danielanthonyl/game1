#pragma once

#include <string>

/**
 * @brief Configuration constants for the game
 *
 * This namespace contains configuration constants and enums
 * used throughout the game.
 */
namespace GameConfig
{
/**
 * @brief Animation state names
 *
 * These string constants are used to identify animation states
 * in a more flexible way than using an enum.
 */
namespace AnimationStates
{
const std::string IDLE = "idle";
const std::string RUNNING = "running";
}  // namespace AnimationStates

/**
 * @brief Resource paths
 *
 * These constants define the paths to various game resources.
 */
namespace ResourcePaths
{
const std::string TEXTURES_DIR = "./";
const std::string TEXTURES_DATAS_DIR = "./";

// texture
const std::string PLAYER_IDLE_TEXTURE = TEXTURES_DIR + "idle.png";
const std::string PLAYER_RUNNING_TEXTURE = TEXTURES_DIR + "running.png";

// texture data
const std::string PLAYER_IDLE_TEXTURE_DATA = TEXTURES_DATAS_DIR + "idle.json";
const std::string PLAYER_RUNNING_TEXTURE_DATA =
    TEXTURES_DATAS_DIR + "running.json";
}  // namespace ResourcePaths

/**
 * @brief Resource IDs
 *
 * These constants define the IDs used to reference resources
 * in the ResourceManager.
 */
namespace ResourceIds
{
const std::string PLAYER_IDLE = "player_idle";
const std::string PLAYER_RUNNING = "player_running";
}  // namespace ResourceIds
}  // namespace GameConfig