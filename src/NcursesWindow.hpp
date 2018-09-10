#pragma once

#include <string>

typedef struct _win_st WINDOW;

namespace perg::types
{
struct Region;
}

namespace perg::tui
{
class Ncurses;

class NcursesWindow
{
 public:
  NcursesWindow(types::Region);
  ~NcursesWindow();

  void wattron_reverse();
  void clear();
  void mvprintw(unsigned, unsigned, std::string);
  void refresh();

 public:
  const unsigned cols;
  const unsigned rows;

 private:
  WINDOW* window;
};
} // namespace perg::tui
