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
  void erase();
  void mvprintw(types::Position, std::string_view);
  void refresh();
  std::string getStr(); // TODO: investigate why name cannot be flat
  void move(types::Position);

 public:
  const std::size_t cols;
  const std::size_t rows;

 private:
  WINDOW* window;
};
} // namespace perg::tui
