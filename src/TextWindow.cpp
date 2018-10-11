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
  window->clear(); // TODO: erase (clear only on focus)
  auto knownSize = textView->waitForSizeAtLeast(window->rows);
  textView->applyFunctionToSlice(
      [this](types::TextView::Iterator begin, types::TextView::Iterator end) {
        std::size_t lineNo = 0;
        for (auto it = begin; it != end; it++)
        {
          const auto& line = *it;
          if (windowPositionInText.x < line.size())
          {
            window->mvprintw(
                types::Position{0, lineNo++}, line.substr(windowPositionInText.x, window->cols));
          }
        }
      },
      windowPositionInText.y,
      std::min(
          knownSize - windowPositionInText.y, std::size_t{window->rows})); // TODO: check conversion
  window->move(cursorPosition);
  window->refresh();
}

void TextWindow::moveCursorDown()
{
  if (cursorPosition.y == window->rows - 1)
  {
    windowPositionInText.y = windowPositionInText.y + window->rows < textView->size()
        ? windowPositionInText.y + 1
        : windowPositionInText.y;
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
    windowPositionInText.y =
        windowPositionInText.y > 0 ? windowPositionInText.y - 1 : windowPositionInText.y;
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
    windowPositionInText.y = windowPositionInText.y + window->rows < maxVisibleTextPositionY
        ? windowPositionInText.y + window->rows
        : maxVisibleTextPositionY;
  }
}

void TextWindow::movePageUp()
{
  windowPositionInText.y =
      windowPositionInText.y > window->rows ? windowPositionInText.y - window->rows : 0;
}

void TextWindow::moveToTheTextEnd()
{
  cursorPosition.x = 0;
  cursorPosition.y = std::min(std::size_t{window->rows}, textView->size()) - 1; // TODO: gsl x 2
  windowPositionInText.x = 0;
  windowPositionInText.y = textView->size() > window->rows ? textView->size() - window->rows : 0;
}

void TextWindow::moveToTheTextBegin()
{
  cursorPosition.x = 0;
  cursorPosition.y = 0;
  windowPositionInText.x = 0;
  windowPositionInText.y = 0;
}

void TextWindow::moveCursorRight()
{
  if (cursorPosition.x == window->cols - 1)
  {
    windowPositionInText.x = windowPositionInText.x + window->cols < getCurrentLine().size() + 1
        ? windowPositionInText.x + 1
        : windowPositionInText.x;
  }
  else
  {
    cursorPosition.x++;
  }
}

void TextWindow::moveCursorLeft()
{
  if (cursorPosition.x == 0)
  {
    windowPositionInText.x = windowPositionInText.x > 0 ? windowPositionInText.x - 1 : 0;
  }
  else
  {
    cursorPosition.x--;
  }
}

void TextWindow::moveCursorOneWordRight()
{
  auto line = getCurrentLine();
  auto cursorPosInText = getCursorPositionInText();
  if (cursorPosInText.x < line.size())
  {
    auto& cursorPosInLine = cursorPosInText.x;
    while (cursorPosInLine < line.size() and not std::isalnum(line[cursorPosInLine]))
    {
      cursorPosInLine++;
    }
    while (cursorPosInLine < line.size() and std::isalnum(line[cursorPosInLine]))
    {
      cursorPosInLine++;
    }
    setCursorPositionInText(cursorPosInText);
  }
}

void TextWindow::moveCursorOneWordLeft()
{
  auto line = getCurrentLine();
  auto cursorPosInText = getCursorPositionInText();
  if (cursorPosInText.x > 0 and line.size() > 0)
  {
    auto& cursorPosInLine = cursorPosInText.x;
    cursorPosInLine = cursorPosInLine >= line.size() ? line.size() - 1 : cursorPosInLine;
    while (--cursorPosInLine > 0 and not std::isalnum(line[cursorPosInLine]))
      ;
    if (cursorPosInLine > 0)
    {
      while (cursorPosInLine > 0 and std::isalnum(line[cursorPosInLine]))
      {
        cursorPosInLine--;
      }
      if (not std::isalnum(line[cursorPosInLine]))
      {
        cursorPosInLine++;
      }
    }
    setCursorPositionInText(cursorPosInText);
  }
}

void TextWindow::moveCursorToLineEnd()
{
  auto currentLine = getCurrentLine();
  if (currentLine.size() < window->cols)
  {
    windowPositionInText.x = 0;
    cursorPosition.x = currentLine.size() - 1;
  }
  else
  {
    windowPositionInText.x = currentLine.size() - window->cols + 1;
    cursorPosition.x = window->cols - 1;
  }
}

void TextWindow::moveCursorToLineBegin()
{
  windowPositionInText.x = 0;
  cursorPosition.x = 0;
}

std::string_view TextWindow::getCurrentLine() const
{
  std::string_view currentLine;
  textView->applyFunctionToSlice(
      [&currentLine](types::TextView::Iterator begin, types::TextView::Iterator) {
        currentLine = *begin;
      },
      windowPositionInText.y + cursorPosition.y,
      1);
  return currentLine;
}

types::Position TextWindow::getCursorPositionInText() const
{
  return {
      cursorPosition.x + windowPositionInText.x,
      cursorPosition.y + windowPositionInText.y,
  };
}

void TextWindow::setCursorPositionInText(types::Position newCursorPositionInText)
{
  if (newCursorPositionInText.x < windowPositionInText.x)
  {
    windowPositionInText.x = newCursorPositionInText.x;
    cursorPosition.x = 0;
  }
  else if (newCursorPositionInText.x > windowPositionInText.x + window->cols - 1)
  {
    windowPositionInText.x = newCursorPositionInText.x - window->cols + 1;
    cursorPosition.x = window->cols - 1;
  }
  else
  {
    cursorPosition.x = newCursorPositionInText.x - windowPositionInText.x;
  }
  // TODO: handle y (extract generic funtion - same for x and y)
}
} // namespace perg::tui
