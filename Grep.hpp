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

  int getGid();
  const std::string& getName();
  const std::vector<Grep>& getGreps();

protected:
  int mGid;
  std::vector<std::string> mLines;
  std::string mName;
  std::vector<Grep> mGreps;

  static int sNextGid;
};
