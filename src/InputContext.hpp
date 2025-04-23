#pragma once

#include <string>
#include <vector>

#include "nlohmann/json.hpp"

namespace InputContext
{
struct Action
{
  std::string type;
  std::string id;
  std::string key;
};

using Context = std::vector<Action>;

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Action, type, id, key);

};  // namespace InputContext