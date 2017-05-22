#include <vector>

#include "Controller.hpp"

Controller::Controller(WINDOW * window)
{
  getmaxyx(stdscr, mRows, mCols);
  mvwprintw(window, 0, 0, "hello world");
}

void Controller::run()
{
  TextWindow tw(0, 0, mCols, mRows-2);
  std::vector<std::string> lines = { "aaaa", "bbbb", "cccc" };
  tw.setContent(lines);
  tw.render();
  getch();
}
