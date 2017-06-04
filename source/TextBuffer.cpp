#include <cassert>

#include "TextBuffer.hpp"

TextBuffer::TextBuffer() :
  mFull(false)
{
}

unsigned TextBuffer::size()
{
  std::lock_guard<std::mutex> lock(mBufferLock);
  return mBuffer.size();
}

bool TextBuffer::isFull()
{
  std::lock_guard<std::mutex> lock(mBufferLock);
  return mFull;
}

void TextBuffer::applyFunctionToSlice(std::function<void(Iterator, Iterator)> function, unsigned pos, unsigned len)
{
  std::lock_guard<std::mutex> lock(mBufferLock);
  assert(pos <= mBuffer.size() && pos+len <= mBuffer.size());
  function(mBuffer.begin()+pos, mBuffer.begin()+pos+len);
}

void TextBuffer::appendData(const Buffer& data)
{
  std::lock_guard<std::mutex> lock(mBufferLock);
  mBuffer.insert(mBuffer.end(), data.begin(), data.end());
}

void TextBuffer::seal()
{
  std::lock_guard<std::mutex> lock(mBufferLock);
  mFull = true;
}
