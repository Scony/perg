#pragma once

#include <vector>
#include <string>

class Grep
{
public:
  Grep(const std::vector<std::string>& lines);
  virtual ~Grep() {};

  const std::vector<std::string>& peekBuffer();
  const std::string& getName();

protected:
  std::vector<std::string> mLines;
  std::string mName;
};
