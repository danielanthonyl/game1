#include "InputAction.hpp"

InputAction::InputAction(const std::string& name)
  : name(name)
{
}

const std::string& InputAction::getName() const
{
  return name;
}

void InputAction::triggerPressed()
{
  for (const auto& callback : pressedCallbacks)
  {
    if (callback)
    {
      callback();
    }
  }
}

void InputAction::triggerReleased()
{
  for (const auto& callback : releasedCallbacks)
  {
    if (callback)
    {
      callback();
    }
  }
}

void InputAction::bindPressed(ActionCallback callback)
{
  pressedCallbacks.push_back(std::move(callback));
}

void InputAction::bindReleased(ActionCallback callback)
{
  releasedCallbacks.push_back(std::move(callback));
}
