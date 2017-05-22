#pragma once

#include <ncurses.h>

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
