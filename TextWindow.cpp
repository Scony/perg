#include "TextWindow.hpp"

TextWindow::TextWindow(int x, int y, int cols, int rows) :
  Window(x, y, cols, rows)
{
  mWindow = newwin(rows, cols, y, x);
}

TextWindow::~TextWindow()
{
  delwin(mWindow);
}

void TextWindow::setContent(std::vector<std::string> const& lines)
{
  mBuffer = lines;
}

void TextWindow::render()
{
  for (int i = 0; i < mRows and i < mBuffer.size(); i++)
    mvwprintw(mWindow, i, 0, mBuffer[i].c_str());

  wgetch(mWindow);
}
