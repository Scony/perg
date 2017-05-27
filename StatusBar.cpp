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

void StatusBar::setContent(std::string content)
{
  std::string rFill = std::string(mCols - content.size() - 4, '-');
  wclear(mWindow);
  mvwprintw(mWindow, 0, 0, ("-- " + content + " " + rFill).c_str());
  wrefresh(mWindow);
}

void StatusBar::render()
{
}
