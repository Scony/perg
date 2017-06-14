#pragma once

#include <ncurses.h>

class Controller
{
public:
  Controller(WINDOW * window);

protected:
  int mCols;
  int mRows;

  WINDOW * mWindow;
};
