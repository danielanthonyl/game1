#include "InputManager.hpp"

#include <fstream>

#include "nlohmann/json.hpp"

InputManager& InputManager::getInstance() {
  static InputManager instance;
  return instance;
}

InputManager::InputManager() {}

bool InputManager::initialize(const std::string& configPath) {
  this->configPath = configPath;
  return reloadBindings();
}

bool InputManager::reloadBindings() {
  try {
    // Clear existing bindings
    actions.clear();
    keyToActionMap.clear();
    previousKeyStates.clear();

    // Load the config file
    std::ifstream file(configPath);
    if (!file.is_open()) {
      spdlog::error("Failed to open input bindings file: {}", configPath);
      return false;
    }

    // Parse the JSON
    nlohmann::json jsonConfig = nlohmann::json::parse(file);
    config = jsonConfig.get<InputBindingConfig::Config>();

    // Process each context and binding
    for (const auto& context : config.contexts) {
      spdlog::info("Loading input context: {}", context.name);

      for (const auto& binding : context.bindings) {
        // Create the action if it doesn't exist
        createAction(binding.actionName);

        // Map the key to the action
        keyToActionMap[binding.key].push_back(binding.actionName);

        // Initialize the previous key state
        previousKeyStates[binding.key] = false;

        spdlog::info("Bound key '{}' ({}) to action '{}'",
                     getKeyName(binding.key), static_cast<int>(binding.key),
                     binding.actionName);
      }
    }

    spdlog::info("Input bindings loaded successfully");
    return true;
  } catch (const std::exception& e) {
    spdlog::error("Failed to load input bindings: {}", e.what());
    return false;
  }
}

void InputManager::processInput() {
  // Check each mapped key
  for (auto& [key, actionNames] : keyToActionMap) {
    bool isPressed = sf::Keyboard::isKeyPressed(key);
    bool wasPressed = previousKeyStates[key];

    // Key was just pressed
    if (isPressed && !wasPressed) {
      for (const auto& actionName : actionNames) {
        if (auto* action = getAction(actionName)) {
          action->triggerPressed();
        }
      }
    }
    // Key was just released
    else if (!isPressed && wasPressed) {
      for (const auto& actionName : actionNames) {
        if (auto* action = getAction(actionName)) {
          action->triggerReleased();
        }
      }
    }

    // Update previous state
    previousKeyStates[key] = isPressed;
  }
}

void InputManager::registerComponent(InputComponent* component) {
  if (component) {
    components.push_back(component);

    // Bind component's callbacks to actions
    for (const auto& [actionName, callback] : component->getPressedBindings()) {
      if (auto* action = getAction(actionName)) {
        action->bindPressed(callback);
      } else {
        auto* newAction = createAction(actionName);
        newAction->bindPressed(callback);
      }
    }

    for (const auto& [actionName, callback] :
         component->getReleasedBindings()) {
      if (auto* action = getAction(actionName)) {
        action->bindReleased(callback);
      } else {
        auto* newAction = createAction(actionName);
        newAction->bindReleased(callback);
      }
    }
  }
}

void InputManager::unregisterComponent(InputComponent* component) {
  if (component) {
    auto it = std::find(components.begin(), components.end(), component);
    if (it != components.end()) {
      components.erase(it);
    }

    // Note: We don't unbind callbacks here because we don't track which
    // callbacks belong to which component. In a more robust implementation,
    // we would need to store this information.
  }
}

InputAction* InputManager::getAction(const std::string& actionName) {
  auto it = actions.find(actionName);
  if (it != actions.end()) {
    return it->second.get();
  }
  return nullptr;
}

InputAction* InputManager::createAction(const std::string& actionName) {
  auto it = actions.find(actionName);
  if (it != actions.end()) {
    return it->second.get();
  }

  auto action = std::make_unique<InputAction>(actionName);
  InputAction* actionPtr = action.get();
  actions[actionName] = std::move(action);
  return actionPtr;
}

std::string InputManager::getKeyName(sf::Keyboard::Key key) const {
  // Simple mapping of common keys to readable names
  switch (key) {
    case sf::Keyboard::Key::A:
      return "A";
    case sf::Keyboard::Key::B:
      return "B";
    case sf::Keyboard::Key::C:
      return "C";
    case sf::Keyboard::Key::D:
      return "D";
    case sf::Keyboard::Key::E:
      return "E";
    case sf::Keyboard::Key::F:
      return "F";
    case sf::Keyboard::Key::G:
      return "G";
    case sf::Keyboard::Key::H:
      return "H";
    case sf::Keyboard::Key::I:
      return "I";
    case sf::Keyboard::Key::J:
      return "J";
    case sf::Keyboard::Key::K:
      return "K";
    case sf::Keyboard::Key::L:
      return "L";
    case sf::Keyboard::Key::M:
      return "M";
    case sf::Keyboard::Key::N:
      return "N";
    case sf::Keyboard::Key::O:
      return "O";
    case sf::Keyboard::Key::P:
      return "P";
    case sf::Keyboard::Key::Q:
      return "Q";
    case sf::Keyboard::Key::R:
      return "R";
    case sf::Keyboard::Key::S:
      return "S";
    case sf::Keyboard::Key::T:
      return "T";
    case sf::Keyboard::Key::U:
      return "U";
    case sf::Keyboard::Key::V:
      return "V";
    case sf::Keyboard::Key::W:
      return "W";
    case sf::Keyboard::Key::X:
      return "X";
    case sf::Keyboard::Key::Y:
      return "Y";
    case sf::Keyboard::Key::Z:
      return "Z";
    case sf::Keyboard::Key::Space:
      return "Space";
    case sf::Keyboard::Key::Enter:
      return "Enter";
    case sf::Keyboard::Key::Escape:
      return "Escape";
    case sf::Keyboard::Key::Up:
      return "Up";
    case sf::Keyboard::Key::Down:
      return "Down";
    case sf::Keyboard::Key::Left:
      return "Left";
    case sf::Keyboard::Key::Right:
      return "Right";
    default:
      return "Unknown";
  }
}
