#pragma once

#include <vector>
#include <string>
#include <mutex>
#include <condition_variable>

class TextBuffer
{
public:
  using Buffer = std::vector<std::string>;
  using Iterator = std::vector<std::string>::iterator;

public:
  std::pair<Iterator, Iterator> slice(unsigned pos, unsigned len);
  unsigned size();
  // void waitForNewData();

  void append(const Buffer& data);

private:
  Buffer mBuffer;
  std::mutex mBufferLock;
  std::condition_variable mNewData;
};
