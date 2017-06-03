#include "TextWindow.hpp"

TextWindow::TextWindow(std::shared_ptr<TextBuffer> buffer, int x, int y, int cols, int rows) :
  Window(x, y, cols, rows),
  mBuffer(buffer)
{
  mWindow = newwin(rows, cols, y, x);
  keypad(mWindow, TRUE);
  mCursorY = 0;
  mTextOffsetY = 0;
}

TextWindow::~TextWindow()
{
  delwin(mWindow);
}

int TextWindow::getCh()
{
  int key = wgetch(mWindow);
  bool unsupportedKey = false;

  while (!unsupportedKey)
    {
      switch (key)
	{
	case KEY_UP:
	  if (mCursorY == 0)
	    {
	      if (mTextOffsetY > 0)
		{
		  mTextOffsetY--;
		  render();
		}
	    }
	  else
	    wmove(mWindow, --mCursorY, 0);
	  break;

	case KEY_DOWN:
	  if (mCursorY == mRows - 1)
	    {
	      if (mBuffer->size() - mTextOffsetY > mRows)
		{
		  mTextOffsetY++;
		  render();
		}
	    }
	  else
	    wmove(mWindow, ++mCursorY, 0);
	  break;

	case KEY_PPAGE:		// PAGE UP
	  mTextOffsetY = mTextOffsetY > mRows ? mTextOffsetY - mRows : 0;
	  render();
	  break;

	case KEY_NPAGE:		// PAGE DOWN
	  {
	    int maxTextOffsetY = mBuffer->size() - mRows;
	    if (maxTextOffsetY < 0)
	      break;
	    mTextOffsetY = mTextOffsetY + mRows < maxTextOffsetY ? mTextOffsetY + mRows : maxTextOffsetY;
	    render();
	    break;
	  }

	default:
	  unsupportedKey = true;
	}

      if (!unsupportedKey)
	key = wgetch(mWindow);
    }

  return key;
}

void TextWindow::render()
{
  wclear(mWindow);
  auto& pos = mTextOffsetY;
  auto len = std::min((unsigned)mRows, mBuffer->size()-pos);
  auto renderer = [&](TextBuffer::Iterator begin, TextBuffer::Iterator end) {
    int i = 0;
    auto it = begin;
    while (it != end)
      {
	mvwprintw(mWindow, i, 0, it->c_str());
	i++;
	it++;
      }
  };
  mBuffer->applyFunctionToSlice(renderer, pos, len);
  wmove(mWindow, mCursorY, 0);
}
