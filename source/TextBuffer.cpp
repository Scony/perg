#include <cassert>

#include "TextBuffer.hpp"

TextBuffer::TextBuffer()
{
}

unsigned TextBuffer::size()
{
  return mBuffer.size();
}

void TextBuffer::applyFunctionToSlice(std::function<void(Iterator, Iterator)> function, unsigned pos, unsigned len)
{
  assert(pos < mBuffer.size() && pos+len <= mBuffer.size());
  function(mBuffer.begin()+pos, mBuffer.begin()+pos+len);
}

void TextBuffer::appendData(const Buffer& data)
{
  mBuffer.insert(mBuffer.end(), data.begin(), data.end());
}
