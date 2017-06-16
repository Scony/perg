#include <cassert>

#include "StaticTextBuffer.hpp"

StaticTextBuffer::StaticTextBuffer(Buffer buffer) :
  mBuffer(buffer)
{
}

unsigned StaticTextBuffer::size()
{
  return mBuffer.size();
}

void StaticTextBuffer::applyFunctionToSlice(std::function<void(Iterator, Iterator)> function,
					    unsigned pos,
					    unsigned len)
{
  assert(pos <= mBuffer.size());
  assert(pos+len <= mBuffer.size());
  function(mBuffer.begin()+pos, mBuffer.begin()+pos+len);
}
