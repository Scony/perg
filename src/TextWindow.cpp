#include "TextWindow.hpp"
#include "NcursesWindow.hpp"

namespace perg::tui
{
TextWindow::TextWindow(std::unique_ptr<NcursesWindow> window, const std::vector<std::string>& lines)
    : window{std::move(window)}, lines{lines}
{
}

void TextWindow::render()
{
  window->clear();
  for (unsigned lineNo = 0; lineNo < lines.size(); lineNo++)
  {
    window->mvprintw(0, lineNo, lines[lineNo]);
  }
  window->refresh();
}
} // namespace perg::tui
