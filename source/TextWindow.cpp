#include "TextWindow.hpp"
#include "Termkey.hpp"

TextWindow::TextWindow(Region region, std::shared_ptr<ITextBuffer> buffer) :
  Window(region),
  mBuffer(buffer),
  mCursorY(0),
  mTextOffsetY(0),
  mPreviousTextOffsetY(-1),
  mPreviousBufferSize(-1)
{
  keypad(mWindow, TRUE);
  wtimeout(mWindow, mWindowTimeoutMs);
}

TextWindow::~TextWindow()
{
}

int TextWindow::getCh()
{
  wrefresh(mWindow);
  Termkey& termkey = Termkey::getInstance();
  Event e = termkey.waitEvent();
  return e.key;

  // int key = wgetch(mWindow);
  int key = -1;
  bool unsupportedKey = false;

  while (!unsupportedKey)
    {
      switch (key)
	{
	case KEY_UP:
	  if (mCursorY == 0)
	    {
	      if (mTextOffsetY > 0)
		mTextOffsetY--;
	    }
	  else
	    wmove(mWindow, --mCursorY, 0);
	  break;

	case KEY_DOWN:
	  if (mCursorY == mRows - 1)
	    {
	      if (mBuffer->size() - mTextOffsetY > mRows)
		mTextOffsetY++;
	    }
	  else
	    wmove(mWindow, ++mCursorY, 0);
	  break;

	case KEY_PPAGE:		// PAGE UP
	  mTextOffsetY = mTextOffsetY > mRows ? mTextOffsetY - mRows : 0;
	  break;

	case KEY_NPAGE:		// PAGE DOWN
	  {
	    int maxTextOffsetY = mBuffer->size() - mRows;
	    if (maxTextOffsetY < 0)
	      break;
	    mTextOffsetY = mTextOffsetY + mRows < maxTextOffsetY ? mTextOffsetY + mRows : maxTextOffsetY;
	    break;
	  }

	default:
	  unsupportedKey = true;
	}

      if (!unsupportedKey)
	{
	  render();
	  key = wgetch(mWindow);
	}
    }

  return key;
}

void TextWindow::render()
{
  if (mPreviousTextOffsetY != mTextOffsetY || mPreviousBufferSize != mBuffer->size())
    {
      mPreviousTextOffsetY = mTextOffsetY;
      mPreviousBufferSize = mBuffer->size();
      forceRender();
    }
}

void TextWindow::focus()
{
  wmove(mWindow, mCursorY, 0);
}

void TextWindow::forceRender()
{
  auto& pos = mTextOffsetY;
  auto len = std::min((unsigned)mRows, mBuffer->size()-pos);
  auto renderer = [&](ITextBuffer::Iterator begin, ITextBuffer::Iterator end) {
    int i = 0;
    auto it = begin;
    while (it != end)
      {
	mvwprintw(mWindow, i, 0, it->c_str());
	i++;
	it++;
      }
  };

  wclear(mWindow);
  mBuffer->applyFunctionToSlice(renderer, pos, len);
  wmove(mWindow, mCursorY, 0);
}
