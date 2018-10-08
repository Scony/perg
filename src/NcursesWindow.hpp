#pragma once

#include <string>

typedef struct _win_st WINDOW;

namespace perg::types
{
struct Region;
struct Position;
} // namespace perg::types

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
  std::string getStr(); // TODO: investigate why name cannot be flat
  void move(types::Position);

 public:
  const unsigned cols;
  const unsigned rows;

 private:
  WINDOW* window;
};
} // namespace perg::tui
