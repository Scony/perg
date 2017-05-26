#include <string>

#include "Minibuffer.hpp"

Minibuffer::Minibuffer(int x, int y, int cols) :
  Window(x, y, cols, 1)
{
  mWindow = newwin(1, cols, y, x);
  // std::string bar = std::string(mCols, '-');
  // wattron(mWindow, A_REVERSE);
  // mvwprintw(mWindow, 0, 0, bar.c_str());
  wrefresh(mWindow);
}

Minibuffer::~Minibuffer()
{
  delwin(mWindow);
}

void Minibuffer::render()
{
}
