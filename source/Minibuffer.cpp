#include <string>

#include "Minibuffer.hpp"

Minibuffer::Minibuffer(Region region) :
  Window(region)
{
  wrefresh(mWindow);
}

Minibuffer::~Minibuffer()
{
}

void Minibuffer::setContent(std::string content)
{
  wclear(mWindow);
  mvwprintw(mWindow, 0, 0, content.c_str());
  wrefresh(mWindow);
}

std::string Minibuffer::readStr()
{
  char buff[255] = { 0 };

  wclear(mWindow);
  echo();
  mvwgetstr(mWindow, 0, 0, buff);
  noecho();
  wclear(mWindow);
  wrefresh(mWindow);

  return std::string(buff);
}

void Minibuffer::render()
{
}
