#include "InputContextComponent.hpp"

#include "NlohmannJsonParser.hpp"
#include "spdlog/spdlog.h"

InputContextComponent::InputContextComponent() {}

void InputContextComponent::bindContext(const std::string& contextId)
{
  activeContext = NlohmannJsonParser::parseInputContext(contextId);
  activeContextId = contextId;
  spdlog::info("Context {} added.", contextId);
}

void InputContextComponent::bindAction(
    const InputContext::ActionHandler& actionHandler)
{
  actionHandlers.push_back(actionHandler);

  spdlog::info("action {} added to bind {}, using context {}",
               actionHandler.action.id, actionHandler.action.key,
               activeContextId);
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
