#include <functional>

#include "Grep.hpp"

using namespace std::placeholders;

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
  auto newGrep = std::make_shared<Grep>(std::bind(&Grep::grepWorker, this, pattern, _1), pattern);
  // mGreps.push_back(g);

  return newGrep;
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

void Grep::grepWorker(std::string pattern, std::shared_ptr<TextBuffer> output)
{
  unsigned knownInputSize = 0;
  bool inputFull = false;
  while (!inputFull)
    {
      mBuffer->waitForNewSize(knownInputSize);
      inputFull = mBuffer->full();
      unsigned newInputSize = mBuffer->size();

      auto& pos = knownInputSize;
      unsigned len = newInputSize - knownInputSize;
      auto filterer = [&](TextBuffer::Iterator begin, TextBuffer::Iterator end) {
	std::vector<std::string> linesMatching;
	auto linesChecked = 0;
	auto it = begin;
	while (it != end)
	  {
	    if (it->find(pattern) != std::string::npos)
	      linesMatching.push_back(*it);
	    it++;
	    linesChecked++;
	    if (linesChecked % mLinesToFlush == 0)
	      {
		output->appendData(std::move(linesMatching));
		linesMatching.clear();
	      }
	  }
	output->appendData(std::move(linesMatching));
      };

      mBuffer->applyFunctionToSlice(filterer, pos, len);
      knownInputSize = newInputSize;
    }
  output->seal();
}
