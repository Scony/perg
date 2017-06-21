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
}

TextWindow::~TextWindow()
{
}

Event TextWindow::proceed()
{
  bool eventSupported = true;
  Event event("");

  do
    {
      Termkey& termkey = Termkey::getInstance();
      event = termkey.waitEvent(mWindowTimeoutMs);

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
	eventSupported = false;

      if (eventSupported)
	lazyRender();
    }
  while (eventSupported);

  return event;
}

void TextWindow::render()
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

void TextWindow::focus()
{
  lazyRender();
}

void TextWindow::lazyRender()
{
  if (mPreviousTextOffsetY != mTextOffsetY)
    {
      mPreviousTextOffsetY = mTextOffsetY;
      mPreviousBufferSize = mBuffer->size();
      render();
      return;
    }
  else if (mPreviousBufferSize != mBuffer->size())
    {
      if (mPreviousBufferSize < mRows)
	{
	  mPreviousBufferSize = mBuffer->size();
	  render();
	  return;
	}
      mPreviousBufferSize = mBuffer->size();
    }

  wrefresh(mWindow);
}
