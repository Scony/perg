#pragma once

#include "Grep.hpp"

class File : public Grep
{
public:
  File(std::string fileName);
};
