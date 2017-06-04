#include "Grep.hpp"

int Grep::sNextGid = 0;

Grep::Grep(std::function<void(std::shared_ptr<TextBuffer>)> workerFunction,
	   std::string name) :
  mGid(sNextGid++),
  mBuffer(new TextBuffer),
  mName(name),
  mThread(workerFunction, mBuffer)
{
}

Grep::~Grep()
{
  if (mThread.joinable())
    mThread.join();
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
  return std::shared_ptr<Grep>(nullptr);
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
