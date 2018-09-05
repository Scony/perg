#include <cassert>
#include <ncurses.h>

#include "KeyboardInput.hpp"

int main()
{
  assert(setenv("TERM", "xterm-256color", 1) == 0);
  perg::tui::KeyboardInput::init();
  initscr();
  printw("It works!");
  refresh();
  perg::tui::KeyboardInput::awaitKeyPressed();
  endwin();
  return 0;
}
