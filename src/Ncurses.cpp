#include <cassert>
#include <ncurses.h>
#include <string>

#include "Ncurses.hpp"
#include "Region.hpp"

namespace perg::tui
{
Ncurses::Ncurses()
{
  assert(setenv("TERM", "xterm-256color", 1) == 0);
  initscr();
}

Ncurses::~Ncurses()
{
  endwin();
}

void Ncurses::printw(const std::string text)
{
  ::printw(text.c_str());
}

void Ncurses::refresh()
{
  ::refresh();
}

Region Ncurses::getRegion()
{
  unsigned cols;
  unsigned rows;
  getmaxyx(stdscr, rows, cols);
  return Region{0, 0, cols, rows};
}
} // namespace perg::tui
