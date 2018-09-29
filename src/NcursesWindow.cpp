#include <ncurses.h>

#include "NcursesWindow.hpp"
#include "Region.hpp"

namespace perg::tui
{
NcursesWindow::NcursesWindow(types::Region region)
    : cols{region.cols}
    , rows{region.rows}
    , window{newwin(region.rows, region.cols, region.y, region.x)}
{
}

NcursesWindow::~NcursesWindow()
{
  delwin(window);
}

void NcursesWindow::wattron_reverse()
{
  wattron(window, A_REVERSE);
}

void NcursesWindow::clear()
{
  wclear(window);
}

void NcursesWindow::mvprintw(unsigned x, unsigned y, std::string str)
{
  mvwprintw(window, y, x, "%s", str.c_str());
}

void NcursesWindow::refresh()
{
  wrefresh(window);
}

std::string NcursesWindow::getStr()
{
  char buff[255] = {0};
  wgetstr(window, buff);
  return std::string(buff);
}
} // namespace perg::tui
