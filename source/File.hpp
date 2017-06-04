#pragma once

#include "Grep.hpp"

class File : public Grep
{
public:
  File(std::string fileName);

private:
  void readFile(std::string fileName, std::shared_ptr<TextBuffer> output);
};
