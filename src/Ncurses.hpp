#pragma once

namespace perg::types
{
struct Region;
}

namespace perg::tui
{
class Ncurses
{
 public:
  Ncurses();
  ~Ncurses();

  void printw(std::string);
  void refresh();
  types::Region getRegion();
};
} // namespace perg::tui
