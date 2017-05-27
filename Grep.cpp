#include "Grep.hpp"

Grep::Grep(const std::vector<std::string>& lines)
{
  mLines = lines;
}

const std::vector<std::string>& Grep::peekBuffer()
{
  return mLines;
}

const std::string& Grep::getName()
{
  return mName;
}
