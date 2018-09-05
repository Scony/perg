#include <ncurses.h>
#include <cassert>

#include "KeyboardInput.hpp"

int main()
{
  assert(setenv("TERM", "xterm-256color", 1) == 0);
  tui::KeyboardInput::init();
  initscr();
  printw("It works!");
  refresh();
  tui::KeyboardInput::awaitKeyPressed();
  endwin();
  return 0;
}
