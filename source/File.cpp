#include <fstream>
#include <stdexcept>
#include <functional>

using namespace std::placeholders;

#include "File.hpp"

File::File(std::string fileName) :
  Grep(std::bind(&File::readFile, this, fileName, _1), fileName)
{
}

void File::readFile(std::string fileName, std::shared_ptr<TextBuffer> output)
{
  std::ifstream fileStream(fileName.c_str());
  if (!fileStream.is_open())
    throw std::runtime_error("Cannot open file");

  std::vector<std::string> lines;
  std::string line;
  while (getline(fileStream, line))
    {
      lines.push_back(line);
      if (lines.size() >= mLinesToFlush)
	{
	  output->appendData(lines);
	  lines.clear();
	}
    }

  output->seal();
}
