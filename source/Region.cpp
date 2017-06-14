#include "Region.hpp"

Region::Region(unsigned aX, unsigned aY, unsigned aCols, unsigned aRows) :
  x(aX),
  y(aY),
  cols(aCols),
  rows(aRows)
{
}

Region Region::windowToRegion(WINDOW * window)
{
  unsigned cols;
  unsigned rows;

  getmaxyx(window, rows, cols);

  return Region(0, 0, cols, rows);
}
