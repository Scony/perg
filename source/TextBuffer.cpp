#include <cassert>

#include "TextBuffer.hpp"

TextBuffer::TextBuffer()
{
}

// std::pair<TextBuffer::Iterator, TextBuffer::Iterator> TextBuffer::slice(unsigned pos, unsigned len)
// {
//   assert(pos < mBuffer.size() && pos+len <= mBuffer.size());
//   return {mBuffer.begin()+pos, mBuffer.begin()+pos+len};
// }

unsigned TextBuffer::size()
{
  return mBuffer.size();
}
