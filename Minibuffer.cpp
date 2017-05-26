#include <string>

#include "Minibuffer.hpp"

Minibuffer::Minibuffer(int x, int y, int cols) :
  Window(x, y, cols, 1)
{
  mWindow = newwin(1, cols, y, x);
  wrefresh(mWindow);
}

Minibuffer::~Minibuffer()
{
  delwin(mWindow);
}

void Minibuffer::setContent(std::string content)
{
  wclear(mWindow);
  mvwprintw(mWindow, 0, 0, content.c_str());
  wrefresh(mWindow);
}

void Minibuffer::render()
{
}
