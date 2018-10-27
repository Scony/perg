#include "StatusBar.hpp"
#include "NcursesWindow.hpp"
#include "types/Position.hpp"

namespace perg::tui
{
StatusBar::StatusBar(std::unique_ptr<NcursesWindow> window) : window{std::move(window)}, text{""}
{
  this->window->wattron_reverse();
}

void StatusBar::setText(const std::string& text)
{
  this->text = text;
}

void StatusBar::render()
{
  std::string rFill = std::string(window->cols - text.size() - 4, '-');
  std::string rawText = "-- " + text + " " + rFill;
  if (text == "")
  {
    rawText = "----" + rFill;
  }

  window->clear();
  window->mvprintw({0, 0}, rawText);
  window->refresh();
}
}; // namespace perg::tui
