#include "Grep.hpp"

Grep::Grep(const std::vector<std::string>& lines, std::string name)
{
  mLines = lines;
  mName = name;
}

const std::vector<std::string>& Grep::peekBuffer()
{
  return mLines;
}

Grep Grep::grep(std::string pattern)
{
  std::vector<std::string> linesMatching;
  for (const auto& line : mLines)
    if (line.find(pattern) != std::string::npos)
      linesMatching.push_back(line);

  Grep g = Grep(linesMatching, pattern);
  mGreps.push_back(g);

  return g;
}

const std::string& Grep::getName()
{
  return mName;
}

const std::vector<Grep>& Grep::getGreps()
{
  return mGreps;
}
