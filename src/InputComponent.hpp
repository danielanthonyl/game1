#pragma once

#include <string>
#include <map>
#include <functional>
#include "InputAction.hpp"

/**
 * @brief Component for handling input actions
 * 
 * This class follows Unreal Engine's approach to input components,
 * where entities can have an input component that binds actions
 * to entity methods.
 */
class InputComponent
{
public:
  InputComponent();
  virtual ~InputComponent() = default;

  /**
   * @brief Bind an action to a callback function (pressed event)
   * 
   * @param actionName The name of the action to bind
   * @param callback The function to call when the action is pressed
   */
  void bindAction(const std::string& actionName, InputAction::ActionCallback callback);

  /**
   * @brief Bind an action to a callback function (released event)
   * 
   * @param actionName The name of the action to bind
   * @param callback The function to call when the action is released
   */
  void bindActionReleased(const std::string& actionName, InputAction::ActionCallback callback);

  /**
   * @brief Get the action bindings
   * 
   * @return Map of action names to callbacks
   */
  const std::map<std::string, InputAction::ActionCallback>& getPressedBindings() const;
  
  /**
   * @brief Get the action release bindings
   * 
   * @return Map of action names to callbacks
   */
  const std::map<std::string, InputAction::ActionCallback>& getReleasedBindings() const;

private:
  std::map<std::string, InputAction::ActionCallback> pressedBindings;
  std::map<std::string, InputAction::ActionCallback> releasedBindings;
};
