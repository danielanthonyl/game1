#include "ControllerComponent.hpp"

#include "Entity.hpp"
#include "InputContext.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFMLKeyMap.hpp"

void ControllerComponent::handleInput(Entity& entity)
{
  const auto& actionHandlers =
      entity.getInputContextComponent().getActionHandlers();

  for (const InputContext::ActionHandler& actionHandler : actionHandlers)
  {
    sf::Keyboard::Key key = SFMLKeyMap::toKey(actionHandler.action.key);

    if (sf::Keyboard::isKeyPressed(key))
    {
      actionHandler.actionCallback();
    }
  }
}