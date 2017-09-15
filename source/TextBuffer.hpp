#pragma once

#include <vector>
#include <string>
#include <mutex>
#include <condition_variable>

#include "ITextBuffer.hpp"

class TextBuffer : public ITextBuffer
{
public:
  TextBuffer();

  unsigned size();
  bool full();
  void applyFunctionToSlice(std::function<void(Iterator, Iterator)> function, unsigned pos, unsigned len);
  void waitForNewSize(unsigned oldSize);

  void appendData(Buffer && data);
  void seal();

private:
  Buffer mBuffer;
  bool mFull;
  std::mutex mBufferLock;
  std::condition_variable mNewData;

private:
  TextBuffer(const TextBuffer&) = delete;
  TextBuffer& operator=(const TextBuffer&) = delete;
  TextBuffer(TextBuffer&&) = delete;
  TextBuffer& operator=(TextBuffer&&) = delete;
};
