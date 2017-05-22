#pragma once

#include <ncurses.h>

#include "TextWindow.hpp"

class Controller
{
public:
  enum Keyboard { PAGE_UP = 339, PAGE_DOWN = 338 };

public:
  Controller(WINDOW * window);

  void run();

private:
  int mCols;
  int mRows;
};
