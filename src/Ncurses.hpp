#pragma once

namespace perg::tui
{
struct Region;

class Ncurses
{
 public:
  Ncurses();
  ~Ncurses();

  void printw(std::string);
  void refresh();
  Region getRegion();
};
} // namespace perg::tui
