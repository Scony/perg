#include "Grep.hpp"

int Grep::sNextGid = 0;

Grep::Grep(std::function<void(std::shared_ptr<TextBuffer>)> workerFunction,
	   std::string name) :
  mGid(sNextGid++),
  mName(name),
  mBuffer(new TextBuffer)
{
  workerFunction(mBuffer);
}

std::shared_ptr<Grep> Grep::grep(std::string pattern)
{
  // std::vector<std::string> linesMatching;
  // for (const auto& line : mLines)
  //   if (line.find(pattern) != std::string::npos)
  //     linesMatching.push_back(line);

  // auto g = std::make_shared<Grep>(linesMatching, pattern);
  // mGreps.push_back(g);

  // return g;
}

int Grep::getGid()
{
  return mGid;
}

std::shared_ptr<TextBuffer> Grep::getBuffer()
{
  return mBuffer;
}

const std::string& Grep::getName()
{
  return mName;
}

// const std::vector<Grep>& Grep::getGreps()
// {
//   return mGreps;
// }
