#pragma once

#include "ITextBuffer.hpp"

class StaticTextBuffer : public ITextBuffer
{
public:
  StaticTextBuffer(Buffer buffer);

  unsigned size() override;
  void applyFunctionToSlice(std::function<void(Iterator, Iterator)> function,
			    unsigned pos,
			    unsigned len) override;

private:
  Buffer mBuffer;
};
