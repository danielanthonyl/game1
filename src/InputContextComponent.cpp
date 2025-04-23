#include "InputContextComponent.hpp"

#include "NlohmannJsonParser.hpp"
#include "spdlog/spdlog.h"

InputContextComponent::InputContextComponent() {}

void InputContextComponent::addContext(const std::string& contextId)
{
  activeContext = NlohmannJsonParser::parseInputContext(contextId);
  spdlog::info("Context {} added.", contextId);
}

const InputContext::Context& InputContextComponent::getActiveContext() const
{
  return activeContext;
}

InputContext::Action InputContextComponent::getAction(
    const std::string& actionId) const
{
  auto it = std::find_if(activeContext.begin(), activeContext.end(),
                         [actionId](InputContext::Action action)
                         { return action.id == actionId; });

  if (it != activeContext.end())
  {
    return *it;
  }

  // spdlog::warn("no action found for id {}", actionId);
  return InputContext::Action();
}
