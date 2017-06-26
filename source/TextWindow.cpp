#include "TextWindow.hpp"
#include "Termkey.hpp"

TextWindow::TextWindow(Region region, std::shared_ptr<ITextBuffer> buffer) :
  Window(region),
  mBuffer(buffer),
  mCursorX(0),
  mCursorY(0),
  mTextOffsetX(0),
  mTextOffsetY(0),
  mPreviousTextOffsetX(-1),
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
  Event event("");

  while (true)
    {
      Termkey& termkey = Termkey::getInstance();
      event = termkey.waitEvent(mWindowTimeoutMs);

      if (mActiveHandlers.find(event.describe()) != mActiveHandlers.end())
	{
	  mActiveHandlers[event.describe()]();
	  lazyRender();
	}
      else
	break;
    }

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
	if (mTextOffsetX < it->length())
	  mvwprintw(mWindow, i, 0, it->substr(mTextOffsetX).c_str());
	i++;
	it++;
      }
  };

  werase(mWindow);
  mBuffer->applyFunctionToSlice(renderer, pos, len);
  wmove(mWindow, mCursorY, mCursorX);
  wrefresh(mWindow);
}

void TextWindow::focus()
{
  lazyRender();
}

void TextWindow::lazyRender()
{
  if (mPreviousTextOffsetX != mTextOffsetX || mPreviousTextOffsetY != mTextOffsetY)
    {
      mPreviousTextOffsetX = mTextOffsetX;
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

void TextWindow::upHandler()
{
  if (mCursorY == 0)
    {
      if (mTextOffsetY > 0)
	mTextOffsetY--;
    }
  else
    wmove(mWindow, --mCursorY, mCursorX);
}

void TextWindow::downHandler()
{
  if (mCursorY == mRows - 1)
    {
      if (mBuffer->size() - mTextOffsetY > mRows)
	mTextOffsetY++;
    }
  else
    wmove(mWindow, ++mCursorY, mCursorX);
}

void TextWindow::leftHandler()
{
  if (mCursorX == 0)
    {
      if (mTextOffsetX > 0)
	mTextOffsetX--;
    }
  else
    wmove(mWindow, mCursorY, --mCursorX);
}

void TextWindow::rightHandler()
{
  if (mCursorX == mCols - 1)
    {
      mTextOffsetX++;	// TODO: calculate local maximum
    }
  else
    wmove(mWindow, mCursorY, ++mCursorX);
}

void TextWindow::pageUpHandler()
{
  mTextOffsetY = mTextOffsetY > mRows ? mTextOffsetY - mRows : 0;
}

void TextWindow::pageDownHandler()
{
  int maxTextOffsetY = mBuffer->size() - mRows;
  if (maxTextOffsetY >= 0)
    mTextOffsetY = mTextOffsetY + mRows < maxTextOffsetY ? mTextOffsetY + mRows : maxTextOffsetY;
}
