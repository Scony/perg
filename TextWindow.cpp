#include "TextWindow.hpp"

TextWindow::TextWindow(int x, int y, int cols, int rows) :
  Window(x, y, cols, rows)
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

void TextWindow::setContent(std::vector<std::string> const& lines)
{
  mBuffer = lines;
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
	      if (mBuffer.size() - mTextOffsetY > mRows)
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
	    int maxTextOffsetY = mBuffer.size() - mRows;
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
  for (int i = 0; i < mRows and i < mBuffer.size(); i++)
    mvwprintw(mWindow, i, 0, mBuffer[i+mTextOffsetY].c_str());
  wmove(mWindow, mCursorY, 0);
}
