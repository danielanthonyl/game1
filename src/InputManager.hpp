#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "InputAction.hpp"
#include "InputBindingConfig.hpp"
#include "InputComponent.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "spdlog/spdlog.h"

/**
 * @brief Manages input actions and bindings
 *
 * This class follows Unreal Engine's approach to input management,
 * where a central manager handles input mapping and dispatching.
 */
class InputManager {
 public:
  /**
   * @brief Get the singleton instance
   *
   * @return Reference to the InputManager instance
   */
  static InputManager& getInstance();

  /**
   * @brief Initialize the input manager
   *
   * @param configPath Path to the input bindings JSON file
   * @return True if initialization succeeded, false otherwise
   */
  bool initialize(const std::string& configPath);

  /**
   * @brief Reload input bindings from the config file
   *
   * @return True if reload succeeded, false otherwise
   */
  bool reloadBindings();

  /**
   * @brief Process input events
   *
   * This should be called each frame to check for input changes
   * and trigger the appropriate actions.
   */
  void processInput();

  /**
   * @brief Register an input component
   *
   * @param component Pointer to the input component to register
   */
  void registerComponent(InputComponent* component);

  /**
   * @brief Unregister an input component
   *
   * @param component Pointer to the input component to unregister
   */
  void unregisterComponent(InputComponent* component);

  /**
   * @brief Get an action by name
   *
   * @param actionName The name of the action to get
   * @return Pointer to the action, or nullptr if not found
   */
  InputAction* getAction(const std::string& actionName);

 private:
  InputManager();
  ~InputManager() = default;

  // Prevent copying
  InputManager(const InputManager&) = delete;
  InputManager& operator=(const InputManager&) = delete;

  // Create an action if it doesn't exist
  InputAction* createAction(const std::string& actionName);

  // Get a readable name for a key
  std::string getKeyName(sf::Keyboard::Key key) const;

  std::string configPath;
  InputBindingConfig::Config config;
  std::map<std::string, std::unique_ptr<InputAction>> actions;
  std::map<sf::Keyboard::Key, std::vector<std::string>> keyToActionMap;
  std::map<sf::Keyboard::Key, bool> previousKeyStates;
  std::vector<InputComponent*> components;
};
