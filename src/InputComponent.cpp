#include "InputComponent.hpp"

InputComponent::InputComponent()
{
}

void InputComponent::bindAction(const std::string& actionName, InputAction::ActionCallback callback)
{
  pressedBindings[actionName] = std::move(callback);
}

void InputComponent::bindActionReleased(const std::string& actionName, InputAction::ActionCallback callback)
{
  releasedBindings[actionName] = std::move(callback);
}

const std::map<std::string, InputAction::ActionCallback>& InputComponent::getPressedBindings() const
{
  return pressedBindings;
}

const std::map<std::string, InputAction::ActionCallback>& InputComponent::getReleasedBindings() const
{
  return releasedBindings;
}
