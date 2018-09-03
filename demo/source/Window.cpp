#include "Window.hpp"

Window::Window(Region region) :
  mWindow(newwin(region.rows, region.cols, region.y, region.x)),
  mCols(region.cols),
  mRows(region.rows)
{
}

Window::~Window()
{
  delwin(mWindow);
}
