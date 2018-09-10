#pragma once

#include <memory>

namespace perg::types
{
struct Region;
}

namespace perg::tui
{
class NcursesWindow;

class Ncurses
{
 public:
  Ncurses();
  ~Ncurses();

  void printw(std::string);
  void refresh();
  types::Region getRegion();
  std::unique_ptr<NcursesWindow> createWindow(types::Region);
};
} // namespace perg::tui
