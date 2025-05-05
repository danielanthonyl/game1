#pragma once

#include <map>
#include <string>

#include "SFML/Window/Keyboard.hpp"

class SFMLKeyMap
{
 public:
  static std::string toString(sf::Keyboard::Key key);
  static sf::Keyboard::Key toKey(const std::string& key);

 private:
  static std::map<sf::Keyboard::Key, std::string> keyToStringMap;
  static std::map<std::string, sf::Keyboard::Key> stringToKeyMap;
};
