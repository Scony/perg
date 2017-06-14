#include <ncurses.h>
#include <vector>
#include <string>

#include "ApplicationController.hpp"

int main(int argc, char ** argv)
{
  initscr();
  keypad(stdscr, TRUE);
  noecho();

  ApplicationController applicationController(stdscr);
  for (int i = 1; i < argc; i++)
    applicationController.openFile(argv[i]);
  applicationController.run();

  endwin();
}
