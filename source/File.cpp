#include <fstream>
#include <stdexcept>
#include <functional>

using namespace std::placeholders;

#include "File.hpp"

File::File(std::string fileName) :
  Grep(std::bind(&File::readFile, this, fileName, _1), fileName),
  mMarks(new Marks)
{
}

std::shared_ptr<Marks> File::getMarks()
{
  return mMarks;
}

void File::readFile(std::string fileName, std::shared_ptr<TextBuffer> output)
{
  std::ifstream fileStream(fileName.c_str());
  if (!fileStream.is_open())
    throw std::runtime_error("Cannot open file");

  std::vector<Line> lines;
  long long lineNumber = 1;
  std::string lineContent;
  while (getline(fileStream, lineContent))
    {
      lines.push_back({lineNumber, lineContent});
      if (lines.size() >= mLinesToFlush)
        {
          output->appendData(std::move(lines));
          lines.clear();
        }
    }

  if (lines.size() > 0)
    output->appendData(std::move(lines));

  output->seal();
}
