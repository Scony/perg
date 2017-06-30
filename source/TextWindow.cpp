#include "TextWindow.hpp"
#include "Termkey.hpp"

TextWindow::TextWindow(Region region,
		       std::shared_ptr<ITextBuffer> buffer,
		       std::shared_ptr<Designations> designations) :
  Window(region),
  mBuffer(buffer),
  mDesignations(designations),
  mCursorX(0),
  mCursorY(0),
  mTextOffsetX(0),
  mTextOffsetY(0),
  mSelectionBeginX(-1),
  mSelectionBeginY(-1),
  mPreviousTextOffsetX(-1),
  mPreviousTextOffsetY(-1),
  mPreviousBufferSize(-1),
  mPreviousDesignationsSize(-1)
{
  keypad(mWindow, TRUE);
  enableStandardMode();
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
    int lineNumber = 0;
    auto line = begin;
    while (line != end)
      {
	if (mTextOffsetX < line->length())
	  mvwprintw(mWindow, lineNumber, 0, line->substr(mTextOffsetX, mCols).c_str());

	if (mTextOffsetX < line->length())
	  {
	    std::string visibleText = line->substr(mTextOffsetX, mCols);
	    for (auto const& designation : *mDesignations)
	      {
		auto designationPos = visibleText.find(designation);
		if (designationPos != std::string::npos)
		  {
		    wattron(mWindow, COLOR_PAIR(1));
		    mvwprintw(mWindow, lineNumber, designationPos, designation.c_str());
		    wattroff(mWindow, COLOR_PAIR(1));
		  }
	      }
	  }

	if (pos + lineNumber == mSelectionBeginY)
	  {
	    int relativeSelectionEnd1X = std::min(std::max(mSelectionBeginX - mTextOffsetX, 0), mCols);
	    int relativeSelectionEnd2X = mCursorX;

	    int relativeSelectionBeginX = std::min(relativeSelectionEnd1X, relativeSelectionEnd2X);
	    int relativeSelectionEndX = std::max(relativeSelectionEnd1X, relativeSelectionEnd2X);

	    std::string fill = "";

	    if (mTextOffsetX < line->length())
	      fill = line->substr(mTextOffsetX + relativeSelectionBeginX, relativeSelectionEndX - relativeSelectionBeginX);

	    if (fill.length() < relativeSelectionEndX - relativeSelectionBeginX)
	      fill += std::string(relativeSelectionEndX - relativeSelectionBeginX - fill.length(), ' ');

	    wattron(mWindow, COLOR_PAIR(2));
	    mvwprintw(mWindow,
		      lineNumber,
		      relativeSelectionBeginX,
		      fill.c_str());
	    wattroff(mWindow, COLOR_PAIR(2));
	  }

	lineNumber++;
	line++;
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

std::string TextWindow::getCurrentLine()
{
  std::string currentLine = "";

  auto pos = mCursorY + mTextOffsetY;
  auto len = 1;
  auto lineFetcher = [&](ITextBuffer::Iterator begin, ITextBuffer::Iterator end) {
    currentLine = *begin;
  };
  mBuffer->applyFunctionToSlice(lineFetcher, pos, len);

  return currentLine;
}

std::string TextWindow::getSelectedText()
{
  if (mSelectionBeginX < 0 || mSelectionBeginY < 0)
    return "";

  int absoluteSelectionBeginX = std::min(mSelectionBeginX, mCursorX);
  int absoluteSelectionEndX = std::max(mSelectionBeginX, mCursorX);
  std::string currentLine = getCurrentLine();

  if (absoluteSelectionBeginX >= currentLine.length())
    {
      selectEndHandler();
      return "";
    }

  selectEndHandler();
  return currentLine.substr(absoluteSelectionBeginX, absoluteSelectionEndX - absoluteSelectionBeginX);
}

void TextWindow::lazyRender()	// TODO: refa
{
  if (mPreviousTextOffsetX != mTextOffsetX || mPreviousTextOffsetY != mTextOffsetY)
    {
      mPreviousTextOffsetX = mTextOffsetX;
      mPreviousTextOffsetY = mTextOffsetY;
      mPreviousBufferSize = mBuffer->size();
      mPreviousDesignationsSize = mDesignations->size();
      render();
      return;
    }
  else if (mSelectionBeginX >= 0 && mSelectionBeginY >= 0)
    {
      mPreviousTextOffsetX = mTextOffsetX;
      mPreviousTextOffsetY = mTextOffsetY;
      mPreviousBufferSize = mBuffer->size();
      mPreviousDesignationsSize = mDesignations->size();
      render();
      return;
    }
  else if (mPreviousDesignationsSize != mDesignations->size())
    {
      mPreviousTextOffsetX = mTextOffsetX;
      mPreviousTextOffsetY = mTextOffsetY;
      mPreviousBufferSize = mBuffer->size();
      mPreviousDesignationsSize = mDesignations->size();
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

void TextWindow::lineBeginHandler()
{
  mCursorX = 0;
  mTextOffsetX = 0;

  wmove(mWindow, mCursorY, mCursorX);
}

void TextWindow::lineEndHandler()
{
  unsigned lineLength = getCurrentLine().length();

  unsigned desiredCursorPosX = lineLength;
  if (desiredCursorPosX > mCols - 1)
    {
      mCursorX = mCols - 1;
      mTextOffsetX = desiredCursorPosX - mCols + 1;
    }
  else
    {
      mCursorX = desiredCursorPosX;
      mTextOffsetX = 0;
    }

  wmove(mWindow, mCursorY, mCursorX);
}

void TextWindow::wordLeftHandler()
{
  std::string line = getCurrentLine();

  unsigned cursorPosInString = mCursorX + mTextOffsetX;
  cursorPosInString = std::min(cursorPosInString, (unsigned)line.length());

  int targetPosInString = cursorPosInString - 1;

  // loook for text
  while (targetPosInString >= 0 && !isalnum(line[targetPosInString]))
    targetPosInString--;

  // look for text end
  while (targetPosInString >= 0 && isalnum(line[targetPosInString]))
    targetPosInString--;

  targetPosInString++;

  int desiredCurorPosX = targetPosInString - mTextOffsetX;

  if (desiredCurorPosX < 0)
    {
      mCursorX = 0;
      mTextOffsetX = targetPosInString;
    }
  else
    mCursorX = desiredCurorPosX;

  wmove(mWindow, mCursorY, mCursorX);
}

void TextWindow::wordRightHandler()
{
  std::string line = getCurrentLine();

  unsigned cursorPosInString = mCursorX + mTextOffsetX;

  int targetPosInString = cursorPosInString;

  if (targetPosInString >= line.length())
    return;

  // loook for text
  while (targetPosInString < line.length() && !isalnum(line[targetPosInString]))
    targetPosInString++;

  // look for text end
  while (targetPosInString < line.length() && isalnum(line[targetPosInString]))
    targetPosInString++;

  int desiredCurorPosX = targetPosInString - mTextOffsetX;

  if (desiredCurorPosX > mCols - 1)
    {
      mCursorX = mCols - 1;
      mTextOffsetX += desiredCurorPosX - mCols + 1;
    }
  else
    mCursorX = desiredCurorPosX;

  wmove(mWindow, mCursorY, mCursorX);
}

void TextWindow::textBeginHandler()
{
  mCursorX = 0;
  mCursorY = 0;
  mTextOffsetX = 0;
  mTextOffsetY = 0;

  wmove(mWindow, mCursorY, mCursorX);
}

void TextWindow::textEndHandler()
{
  mCursorX = 0;
  mCursorY = std::min(mRows - 1, mPreviousBufferSize - 1);
  mTextOffsetX = 0;
  mTextOffsetY = std::max(mPreviousBufferSize - mRows, 0);

  wmove(mWindow, mCursorY, mCursorX);
}

void TextWindow::selectBeginHandler()
{
  mSelectionBeginX = mCursorX + mTextOffsetX;
  mSelectionBeginY = mCursorY + mTextOffsetY;

  enableTextSelectionMode();
}

void TextWindow::selectEndHandler()
{
  mSelectionBeginX = -1;
  mSelectionBeginY = -1;

  enableStandardMode();
  render();
}

void TextWindow::enableStandardMode()
{
  mActiveHandlers = mStandardModeHandlers;
}

void TextWindow::enableTextSelectionMode()
{
  mActiveHandlers = mTextSelectionModeHandlers;
}
