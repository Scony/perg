#pragma once

#include "Grep.hpp"
#include "Mark.hpp"

class File : public Grep
{
public:
  File(std::string fileName);

  std::shared_ptr<Marks> getMarks();

private:
  void readFile(std::string fileName, std::shared_ptr<TextBuffer> output);

  std::shared_ptr<Marks> mMarks;
};
