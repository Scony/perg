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

#pragma push_macro("attron")
#undef attron
  void attron();
#pragma pop_macro("attron")
  void attron_reverse();
#pragma push_macro("attroff")
#undef attroff
  void attroff();
#pragma pop_macro("attroff")
  void clear();
  void erase();
  void mvprintw(types::Position, std::string_view);
  void refresh();
#pragma push_macro("getstr")
#undef getstr
  std::string getstr();
#pragma pop_macro("getstr")
  void move(types::Position);

 public:
  const std::size_t cols;
  const std::size_t rows;

 private:
  WINDOW* window;
};
} // namespace perg::tui
