#include "StatusBar.hpp"
#include "NcursesWindow.hpp"

namespace perg::tui
{
StatusBar::StatusBar(std::unique_ptr<NcursesWindow> window)
    : window{std::move(window)}, text{"dummy status"}
{
  this->window->wattron_reverse();
}

void StatusBar::render()
{
  std::string rFill = std::string(window->cols - text.size() - 4, '-');
  std::string rawText = "-- " + text + " " + rFill;

  window->clear();
  window->mvprintw(0, 0, rawText);
  window->refresh();
}
}; // namespace perg::tui
