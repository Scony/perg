#include "TextWindow.hpp"
#include "NcursesWindow.hpp"
#include "types/TextView.hpp"

namespace perg::tui
{
TextWindow::TextWindow(
    std::unique_ptr<NcursesWindow> window,
    std::shared_ptr<types::TextView> textView)
    : window{std::move(window)}, textView{textView}
{
}

void TextWindow::render()
{
  window->clear();
  auto knownSize = textView->waitForSizeAtLeast(window->rows);
  textView->applyFunctionToSlice(
      [&](types::TextView::Iterator begin, types::TextView::Iterator end) {
        unsigned lineNo = 0;
        for (auto it = begin; it != end; it++)
          window->mvprintw(0, lineNo++, std::string(*it));
      },
      visibleTextPosition.y,
      std::min(
          knownSize - visibleTextPosition.y, std::size_t{window->rows})); // TODO: check conversion
  window->move(cursorPosition);
  window->refresh();
}

void TextWindow::moveCursorDown()
{
  if (cursorPosition.y == window->rows - 1)
  {
    visibleTextPosition.y = visibleTextPosition.y + window->rows < textView->size()
        ? visibleTextPosition.y + 1
        : visibleTextPosition.y;
  }
  else
  {
    cursorPosition.y++;
  }
}

void TextWindow::moveCursorUp()
{
  if (cursorPosition.y == 0)
  {
    visibleTextPosition.y =
        visibleTextPosition.y > 0 ? visibleTextPosition.y - 1 : visibleTextPosition.y;
  }
  else
  {
    cursorPosition.y--;
  }
}

void TextWindow::movePageDown()
{
  if (textView->size() > window->rows)
  {
    auto maxVisibleTextPositionY = textView->size() - window->rows;
    visibleTextPosition.y = visibleTextPosition.y + window->rows < maxVisibleTextPositionY
        ? visibleTextPosition.y + window->rows
        : maxVisibleTextPositionY;
  }
}

void TextWindow::movePageUp()
{
  visibleTextPosition.y =
      visibleTextPosition.y > window->rows ? visibleTextPosition.y - window->rows : 0;
}

void TextWindow::moveToTheTextEnd()
{
  cursorPosition.x = 0;
  cursorPosition.y = std::min(std::size_t{window->rows}, textView->size()) - 1; // TODO: gsl x 2
  visibleTextPosition.x = 0;
  visibleTextPosition.y = textView->size() > window->rows ? textView->size() - window->rows : 0;
}

void TextWindow::moveToTheTextBegin()
{
  cursorPosition.x = 0;
  cursorPosition.y = 0;
  visibleTextPosition.x = 0;
  visibleTextPosition.y = 0;
}
} // namespace perg::tui
