#pragma once

#include <vector>
#include <string>

class Grep
{
public:
  Grep(const std::vector<std::string>& lines);
  virtual ~Grep() {};

  const std::vector<std::string>& peekBuffer();

protected:
  std::vector<std::string> mLines;
};
