#pragma once

#include <string>

struct Line
{
  Line(long long aNumber, std::string aContent) : number(aNumber), content(aContent) {}

  long long number;
  std::string content;
};
