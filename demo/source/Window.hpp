#pragma once

#include <ncurses.h>

#include "Region.hpp"

class Window
{
public:
  Window(Region region);
  virtual ~Window();

  virtual void render() = 0;

protected:
  WINDOW * mWindow;
  int mCols;
  int mRows;
};
