#pragma once

#include <vector>
#include <string>
#include <functional>

#include "Line.hpp"

class ITextBuffer
{
public:
  using Buffer = std::vector<Line>;
  using Iterator = std::vector<Line>::iterator;

public:
  virtual ~ITextBuffer() {};

  virtual unsigned size() = 0;
  virtual void applyFunctionToSlice(std::function<void(Iterator, Iterator)> function,
				    unsigned pos,
				    unsigned len) = 0;
};
