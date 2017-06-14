#pragma once

#include <ncurses.h>

struct Region
{
  Region(unsigned aX, unsigned aY, unsigned aCols, unsigned aRows);

  static Region windowToRegion(WINDOW * window);

  const unsigned x;
  const unsigned y;
  const unsigned cols;
  const unsigned rows;
};
