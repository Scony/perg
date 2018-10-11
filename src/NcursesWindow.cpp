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

void NcursesWindow::wattron_reverse()
{
  ::wattron(window, A_REVERSE);
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

std::string NcursesWindow::getStr()
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
