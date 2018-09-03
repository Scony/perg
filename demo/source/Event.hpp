#pragma once

#include <string>

#include "termkey.h"

class Event
{
public:
  Event(TermKeyKey termKeyKey);
  Event(std::string keyString);

  bool operator==(const Event& otherEvent);
  bool operator!=(const Event& otherEvent);

  std::string describe();

private:
  std::string mKey;
};
