#pragma once

#include "../InputContext.hpp"
#include "spdlog/spdlog.h"
#include "SFML/Window/Keyboard.hpp"
#include <unordered_map>

class Entity;

class InputContextComponent
{
 public:
  InputContextComponent();


  /**
   * @brief add and swaps contexts.
   * maybe in the future when multiple contexts are implemented,
   * a "switch context" will be more appropriate
   */
  void bindContext(const std::string& context);

  template <typename T>
  void bindAction(const InputContext::Action& action, void (T::*func)(InputContext::TriggerEvent),
                  T* instance)
  {
    std::function<void(InputContext::TriggerEvent)> actionCallback =
        std::bind(func, instance, std::placeholders::_1);

    InputContext::ActionHandler actionHandler{action, actionCallback};

    actionHandlers.push_back(std::move(actionHandler));

    spdlog::info("action {} added to bind {}, using context {}", action.id,
                 action.key, activeContextId);
  }


  void handleInput();

  // getters
  const InputContext::Context& getActiveContext() const;
  const std::vector<InputContext::ActionHandler>& getActionHandlers() const;
  const InputContext::Action* getAction(const std::string& actionId) const;

 private:
  InputContext::Context activeContext;
  std::string activeContextId;
  std::vector<InputContext::ActionHandler> actionHandlers;
  std::unordered_map<sf::Keyboard::Key, bool> keyStates;
};