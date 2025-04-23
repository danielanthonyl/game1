#pragma once

#include <map>
#include <string>
#include <vector>

#include "SFML/Window/Keyboard.hpp"
#include "nlohmann/json.hpp"

/**
 * @brief Configuration structures for input bindings
 *
 * These structures define the data format for input bindings
 * that can be serialized to/from JSON.
 */
namespace InputBindingConfig {
/**
 * @brief Represents a single input binding
 */
struct InputBinding {
  std::string actionName;
  sf::Keyboard::Key key;
};

/**
 * @brief Represents a collection of input bindings for a context
 */
struct InputContext {
  std::string name;
  std::vector<InputBinding> bindings;
};

/**
 * @brief Root configuration containing all input contexts
 */
struct Config {
  std::vector<InputContext> contexts;
};
}  // namespace InputBindingConfig

// JSON serialization for sf::Keyboard::Key
namespace nlohmann {
template <>
struct adl_serializer<sf::Keyboard::Key> {
  static void to_json(json& j, const sf::Keyboard::Key& key) {
    j = static_cast<int>(key);
  }

  static void from_json(const json& j, sf::Keyboard::Key& key) {
    key = static_cast<sf::Keyboard::Key>(j.get<int>());
  }
};

// JSON serialization for InputBindingConfig::InputBinding
template <>
struct adl_serializer<InputBindingConfig::InputBinding> {
  static void to_json(json& j,
                      const InputBindingConfig::InputBinding& binding) {
    j = json{{"actionName", binding.actionName}, {"key", binding.key}};
  }

  static void from_json(const json& j,
                        InputBindingConfig::InputBinding& binding) {
    j.at("actionName").get_to(binding.actionName);
    j.at("key").get_to(binding.key);
  }
};

// JSON serialization for InputBindingConfig::InputContext
template <>
struct adl_serializer<InputBindingConfig::InputContext> {
  static void to_json(json& j,
                      const InputBindingConfig::InputContext& context) {
    j = json{{"name", context.name}, {"bindings", context.bindings}};
  }

  static void from_json(const json& j,
                        InputBindingConfig::InputContext& context) {
    j.at("name").get_to(context.name);
    j.at("bindings").get_to(context.bindings);
  }
};

// JSON serialization for InputBindingConfig::Config
template <>
struct adl_serializer<InputBindingConfig::Config> {
  static void to_json(json& j, const InputBindingConfig::Config& config) {
    j = json{{"contexts", config.contexts}};
  }

  static void from_json(const json& j, InputBindingConfig::Config& config) {
    j.at("contexts").get_to(config.contexts);
  }
};
}  // namespace nlohmann
