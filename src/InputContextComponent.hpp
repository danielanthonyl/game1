#pragma once

#include "InputContext.hpp"

class InputContextComponent
{
 public:
  InputContextComponent();

  /**
   * @brief swaps contexts.
   * maybe in the future when multiple contexts are implemented,
   * a "switch context" will be more appropriate
   */
  void addContext(const std::string& context);

  const InputContext::Context& getActiveContext() const;

  /**
   * @brief maybe in the future it can encapsulate the SFMLKeyMap
   * and add to the action a specific key like, sf::Keyboard::Key sfmlKey;
   */
  InputContext::Action getAction(const std::string& actionId) const;

 private:
  InputContext::Context activeContext;
  InputContext::Action action;
};
