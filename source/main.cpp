#include <ncurses.h>
#include <vector>
#include <string>

#include "Controller.hpp"

int main(int argc, char ** argv)
{
  std::vector<std::string> fileNames;

  for (int i = 1; i < argc; i++)
    fileNames.emplace_back(argv[i]);

  initscr();
  keypad(stdscr, TRUE);
  noecho();

  Controller controller(stdscr, fileNames);
  controller.run();

  endwin();
}
