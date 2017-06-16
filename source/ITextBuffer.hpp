#pragma once

#include <vector>
#include <string>
#include <functional>

class ITextBuffer
{
public:
  using Buffer = std::vector<std::string>;
  using Iterator = std::vector<std::string>::iterator;

public:
  virtual ~ITextBuffer() {};

  virtual unsigned size() = 0;
  virtual void applyFunctionToSlice(std::function<void(Iterator, Iterator)> function,
				    unsigned pos,
				    unsigned len) = 0;
};
