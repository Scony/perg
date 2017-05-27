#pragma once

#include <vector>
#include <string>

class Grep
{
public:
  Grep(const std::vector<std::string>& lines, std::string name = "");
  virtual ~Grep() {};

  const std::vector<std::string>& peekBuffer();
  Grep grep(std::string pattern);

  const std::string& getName();
  const std::vector<Grep>& getGreps();

protected:
  std::vector<std::string> mLines;
  std::string mName;
  std::vector<Grep> mGreps;
};
