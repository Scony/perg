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
  // wtimeout(mWindow, mWindowTimeoutMs);
}

TextWindow::~TextWindow()
{
}

Event TextWindow::proceed()
{
  wrefresh(mWindow);

  Termkey& termkey = Termkey::getInstance();
  Event event = termkey.waitEvent();

  bool unsupportedEvent = false;

  while (!unsupportedEvent)
    {
      if (event == Event("<Up>"))
	{
	  if (mCursorY == 0)
	    {
	      if (mTextOffsetY > 0)
		mTextOffsetY--;
	    }
	  else
	    wmove(mWindow, --mCursorY, 0);
	}
      else if (event == Event("<Down>"))
	{
	  if (mCursorY == mRows - 1)
	    {
	      if (mBuffer->size() - mTextOffsetY > mRows)
		mTextOffsetY++;
	    }
	  else
	    wmove(mWindow, ++mCursorY, 0);
	}
      else if (event == Event("<PageUp>"))
	{
	  mTextOffsetY = mTextOffsetY > mRows ? mTextOffsetY - mRows : 0;
	}
      else if (event == Event("<PageDown>"))
	{
	  int maxTextOffsetY = mBuffer->size() - mRows;
	  if (maxTextOffsetY >= 0)
	    mTextOffsetY = mTextOffsetY + mRows < maxTextOffsetY ? mTextOffsetY + mRows : maxTextOffsetY;
	}
      else
	unsupportedEvent = true;

      if (!unsupportedEvent)
	{
	  render();
	  wrefresh(mWindow);
	  event = termkey.waitEvent();
	}
    }

  return event;
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
  wrefresh(mWindow);
}
