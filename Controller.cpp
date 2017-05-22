#include <vector>

#include "Controller.hpp"
#include "TextWindow.hpp"
#include "StatusBar.hpp"

Controller::Controller(WINDOW * window)
{
  getmaxyx(stdscr, mRows, mCols);
  mvwprintw(window, 0, 0, "hello world");
}

void Controller::run()
{
  TextWindow tw(0, 0, mCols, mRows-2);
  StatusBar sb(0, mRows-2, mCols);
  StatusBar sb2(0, mRows-1, mCols);

  std::vector<std::string> lines;
  lines.push_back("x");
  for (int i = 1; i < mRows*3; i++)
    lines.push_back(lines[i-1] + "x");

  tw.setContent(lines);
  tw.render();
  tw.getCh();
}
