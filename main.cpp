#include <iostream>
#include <ncurses.h>

#include "Controller.hpp"

int main(int argc, char ** argv)
{
  // if (argc < 2)
  //   {
  //     std::cerr << "Usage: ./a.out [FILE_NAME]" << std::endl;
  //     return 1;
  //   }

  initscr();
  keypad(stdscr, TRUE);
  noecho();

  Controller controller(stdscr);
  controller.run();

  endwin();
}
