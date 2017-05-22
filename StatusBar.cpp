#include <string>

#include "StatusBar.hpp"

StatusBar::StatusBar(int x, int y, int cols) :
  Window(x, y, cols, 1)
{
  mWindow = newwin(1, cols, y, x);
  std::string bar = std::string(mCols, '-');
  wattron(mWindow, A_REVERSE);
  mvwprintw(mWindow, 0, 0, bar.c_str());
  wrefresh(mWindow);
}

StatusBar::~StatusBar()
{
  delwin(mWindow);
}

void StatusBar::render()
{
}
