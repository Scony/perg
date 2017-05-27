#include <fstream>
#include <stdexcept>

#include "File.hpp"

File::File(std::string fileName) :
  Grep(std::vector<std::string>())
{
  mName = fileName;

  std::ifstream fileStream(fileName.c_str());
  if (!fileStream.is_open())
    throw std::runtime_error("Cannot open file");

  std::string line;
  while (getline(fileStream, line))
    mLines.push_back(line);
}
