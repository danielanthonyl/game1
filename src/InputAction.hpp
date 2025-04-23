#pragma once

#include <string>
#include <functional>

/**
 * @brief Represents a logical game action triggered by input
 * 
 * This class follows Unreal Engine's approach to input actions,
 * where actions have a name and can be bound to callback functions.
 */
class InputAction
{
public:
  // Callback type for action events (pressed/released)
  using ActionCallback = std::function<void()>;

  /**
   * @brief Constructor
   * 
   * @param name The name of the action
   */
  explicit InputAction(const std::string& name);

  /**
   * @brief Get the name of the action
   * 
   * @return The action name
   */
  const std::string& getName() const;

  /**
   * @brief Trigger the action (pressed)
   * 
   * This calls all registered pressed callbacks.
   */
  void triggerPressed();

  /**
   * @brief Trigger the action (released)
   * 
   * This calls all registered released callbacks.
   */
  void triggerReleased();

  /**
   * @brief Bind a callback to the action's pressed event
   * 
   * @param callback The function to call when the action is pressed
   */
  void bindPressed(ActionCallback callback);

  /**
   * @brief Bind a callback to the action's released event
   * 
   * @param callback The function to call when the action is released
   */
  void bindReleased(ActionCallback callback);

private:
  std::string name;
  std::vector<ActionCallback> pressedCallbacks;
  std::vector<ActionCallback> releasedCallbacks;
};
