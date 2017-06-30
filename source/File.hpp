#pragma once

#include "Grep.hpp"
#include "Designations.hpp"

class File : public Grep
{
public:
  File(std::string fileName);

  std::shared_ptr<Designations> getDesignations();

private:
  void readFile(std::string fileName, std::shared_ptr<TextBuffer> output);

  std::shared_ptr<Designations> mDesignations;
};
