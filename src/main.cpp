#include <ncurses.h>

int main()
{
  initscr();
  printw("It works!");
  refresh();
  getch();
  endwin();
  return 0;
}
