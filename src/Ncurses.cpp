#include <cassert>
#include <ncurses.h>
#include <string>

#include "Ncurses.hpp"
#include "NcursesWindow.hpp"
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

types::Region Ncurses::getRegion()
{
  unsigned cols;
  unsigned rows;
  getmaxyx(stdscr, rows, cols);
  return types::Region{0, 0, cols, rows};
}

std::unique_ptr<NcursesWindow> Ncurses::createWindow(types::Region region)
{
  return std::make_unique<NcursesWindow>(region);
}
} // namespace perg::tui
