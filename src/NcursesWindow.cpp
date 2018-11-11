#include <ncurses.h>

#include "NcursesWindow.hpp"
#include "Position.hpp"
#include "Region.hpp"

namespace perg::tui
{
NcursesWindow::NcursesWindow(types::Region region)
    : cols{region.cols}
    , rows{region.rows}
    , window{::newwin(region.rows, region.cols, region.y, region.x)}
{
}

NcursesWindow::~NcursesWindow()
{
  ::delwin(window);
}

#pragma push_macro("attron")
#undef attron
void NcursesWindow::attron()
#pragma pop_macro("attron")
{
  ::wattron(window, COLOR_PAIR(1));
}

void NcursesWindow::attron_reverse()
{
  ::wattron(window, A_REVERSE);
}

#pragma push_macro("attroff")
#undef attroff
void NcursesWindow::attroff()
#pragma pop_macro("attroff")
{
  ::wattroff(window, COLOR_PAIR(1));
}

void NcursesWindow::erase()
{
  ::werase(window);
}

void NcursesWindow::clear()
{
  ::wclear(window);
}

void NcursesWindow::mvprintw(types::Position pos, std::string_view str)
{
  ::mvwprintw(window, pos.y, pos.x, "%s", std::string(str).c_str());
}

void NcursesWindow::refresh()
{
  ::wrefresh(window);
}

#pragma push_macro("getstr")
#undef getstr
std::string NcursesWindow::getstr()
#pragma pop_macro("getstr")
{
  char buff[255] = {0};
  ::wgetstr(window, buff);
  return std::string(buff);
}

void NcursesWindow::move(types::Position position)
{
  ::wmove(window, position.y, position.x);
}
} // namespace perg::tui
