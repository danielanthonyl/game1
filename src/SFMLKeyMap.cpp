#include "SFMLKeyMap.hpp"

std::map<sf::Keyboard::Key, std::string> SFMLKeyMap::keyToStringMap = {
    {sf::Keyboard::Key::W, "W"},         {sf::Keyboard::Key::A, "A"},
    {sf::Keyboard::Key::S, "S"},         {sf::Keyboard::Key::D, "D"},
    {sf::Keyboard::Key::Space, "SPACE"},
};

std::string SFMLKeyMap::toString(sf::Keyboard::Key key)
{
  auto it = keyToStringMap.find(key);

  return it != keyToStringMap.end() ? it->second : "UNKNOWN";
}

sf::Keyboard::Key SFMLKeyMap::toKey(const std::string& key)
{
  for (const auto& pair : keyToStringMap)
  {
    if (pair.second == key)
    {
      return pair.first;
    }
  }

  return sf::Keyboard::Key::Unknown;
}
