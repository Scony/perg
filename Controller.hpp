#pragma once

#include <ncurses.h>
#include <vector>
#include <string>

#include "File.hpp"

class Controller
{
public:
  enum Keyboard { PAGE_UP = 339, PAGE_DOWN = 338 };

public:
  Controller(WINDOW * window, const std::vector<std::string>& fileNames);

  void run();

private:
  int mCols;
  int mRows;

  std::vector<File> mFiles;
};
