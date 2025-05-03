#pragma once

#include "InputContext.hpp"

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
  void bindAction(const InputContext::ActionHandler& actionHandler);

  // getters
  const InputContext::Context& getActiveContext() const;
  const std::vector<InputContext::ActionHandler>& getActionHandlers() const;
  const InputContext::Action* getAction(const std::string& actionId) const;

 private:
  InputContext::Context activeContext;
  std::string activeContextId;
  std::vector<InputContext::ActionHandler> actionHandlers;
};
