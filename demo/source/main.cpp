#include <ncurses.h>
#include <vector>
#include <string>
#include <cassert>
#include <stdlib.h>

#include "ApplicationController.hpp"
#include "Region.hpp"
#include "Termkey.hpp"

void initColorPairs();

int main(int argc, char ** argv)
{
  assert(setenv("TERM", "xterm-256color", 1) == 0);
  Termkey::init();
  initscr();
  keypad(stdscr, TRUE);
  assert(start_color() == OK);
  assert(COLORS >= 8);
  initColorPairs();
  noecho();

  ApplicationController applicationController(Region::windowToRegion(stdscr));
  for (int i = 1; i < argc; i++)
    applicationController.openFile(argv[i]);
  applicationController.run();

  endwin();
}

void initColorPairs()
{
  // static ones
  init_pair(1, COLOR_WHITE, COLOR_BLUE); // reserved
  init_pair(2, COLOR_BLACK, COLOR_RED);
  init_pair(3, COLOR_BLACK, COLOR_GREEN);
  init_pair(4, COLOR_BLACK, COLOR_YELLOW);
  init_pair(5, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(6, COLOR_BLACK, COLOR_CYAN);
  init_pair(7, COLOR_BLACK, COLOR_WHITE);

  // dynamic ones
  for (int colorNum = 8; colorNum < COLORS; colorNum++)
    {
      short r, g, b;
      color_content(colorNum, &r, &g, &b);
      double relativeLuminance = (0.299 * r) + (0.587 * g) + (0.114 * b);
      // double relativeLuminance = 0.2126 * r + 0.7152 * g + 0.0722 * b;

      if (relativeLuminance > 500.0)
	init_pair(colorNum, COLOR_BLACK, colorNum);
      else
	init_pair(colorNum, COLOR_WHITE, colorNum);
    }
}
