#include "InputContextComponent.hpp"

#include "../NlohmannJsonParser.hpp"

#include "../Entity.hpp"
#include "../InputContext.hpp"
#include "../SFMLKeyMap.hpp"



InputContextComponent::InputContextComponent() {}

/**
 * DEBT! why resource manager isn't dealing with this?
 */
void InputContextComponent::bindContext(const std::string& contextId)
{
  activeContext = NlohmannJsonParser::parseInputContext(contextId);
  activeContextId = contextId;
  spdlog::info("Context {} added.", contextId);
}

void InputContextComponent::handleInput()
{
  for (const InputContext::ActionHandler& actionHandler : actionHandlers)
  {
    // DEBT! can be pre-computed instead of called at every frame.
    sf::Keyboard::Key key = SFMLKeyMap::toKey(actionHandler.action.key);

    bool currentlyPressed = sf::Keyboard::isKeyPressed(key);
    bool& wasPressed = keyStates[key];

    if (currentlyPressed && !wasPressed)  // pressed
    {
      wasPressed = true;
      spdlog::info("just pressed");
      actionHandler.actionCallback(InputContext::TriggerEvent::Pressed);
    }
    else if (!currentlyPressed && wasPressed)  // released
    {
      spdlog::info("just released");
      wasPressed = false;
      actionHandler.actionCallback(InputContext::TriggerEvent::Released);
    }
    else if (currentlyPressed && wasPressed)  // held
    {
      spdlog::info("held");
      wasPressed = true;
      actionHandler.actionCallback(InputContext::TriggerEvent::Held);
    }
    else  // default
    {}
  }
}

const InputContext::Context& InputContextComponent::getActiveContext() const
{
  return activeContext;
}

const std::vector<InputContext::ActionHandler>&
InputContextComponent::getActionHandlers() const
{
  return actionHandlers;
}

const InputContext::Action* InputContextComponent::getAction(
    const std::string& actionId) const
{
  auto it = std::find_if(activeContext.begin(), activeContext.end(),
                         [actionId](const InputContext::Action action)
                         { return action.id == actionId; });

  if (it != activeContext.end())
  {
    return &(*it);
  }

  return nullptr;
}
